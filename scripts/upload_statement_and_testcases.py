from lib.api import Client
from lib.parser import load_problem, parse_id_in_contest
from sys import argv
from pathlib import Path
from pack_testcases import make_zip
import logging

logger = logging.getLogger(__name__)

def upload_statement_and_testcases(username: str, password: str):
    client = Client()
    client.login(username, password)

    for path in Path('./').glob('*'):
        if not path.is_dir() or not (path / 'PROBLEM').exists():
            continue

        make_zip(path)
        
        # 設定ファイルの読み込み
        problem_toml_path = path / 'problem.toml'
        problem_rime_path = path / 'PROBLEM'

        if not problem_toml_path.exists():
            logger.warning(f'problem.toml not found in {path.name}')
            continue
        if not problem_rime_path.exists():
            logger.warning(f'PROBLEM not found in {path.name}')
            continue

        problem_toml = open(problem_toml_path, 'r').read()
        problem_rime = open(problem_rime_path, 'r').read()
        
        # 問題文の読み込み
        statement_path = path / 'ss-out' / f'{parse_id_in_contest(problem_toml)}.md'
        if not statement_path.exists():
            logger.warning(f'Statement file not found: {statement_path}')

        statement = open(statement_path, 'r').read()
        problem_id, problem, testcase_sets = load_problem(statement, problem_rime, problem_toml)

        client.upload_testcases(problem_id, f'{path.name}.zip')

        client.put_problem(problem_id, problem)
        
        client.initialize_testcase_sets(problem_id)
        for testcase_set in testcase_sets:
            testcase_ids = client.get_testcase_ids_regex(problem_id, testcase_set.regex)
            if testcase_set.is_sample() or testcase_set.is_all():
                client.put_testcase_set(problem_id, testcase_set)
            else:
                client.post_testcase_set(problem_id, testcase_set)
            testcase_set_id = client.get_testcase_set_id(problem_id, testcase_set.name)
            client.testcases_change_state_multiple(problem_id, testcase_ids, testcase_set_id)
        
        testcases = client.get_testcases(problem_id)[1]
        for explanation_path in (path / 'tests').glob('*.md'):
            md = open(explanation_path, 'r').read()
            testcase_name = explanation_path.stem
            testcase_id = [testcase.id for testcase in testcases if testcase.name == testcase_name][0]
            testcase = client.get_testcase(problem_id, testcase_id)
            testcase.explanation = md
            client.put_testcase(problem_id, testcase_id, testcase)

if __name__ == '__main__':
    upload_statement_and_testcases(argv[1], argv[2])