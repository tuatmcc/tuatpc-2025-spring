from lib.api import Client
from lib.parser import load_problem, parse_id_in_contest
from sys import argv
from pathlib import Path
from pack_testcases import make_zip
from typing import Optional, Tuple
from lib.logger import logger
from time import time

def load_setting_files(base_path: Path) -> Optional[Tuple[str, str]]:
    problem_toml_path = base_path / 'problem.toml'
    problem_rime_path = base_path / 'PROBLEM'

    if not problem_toml_path.exists():
        logger.warning(f'problem.toml not found in {base_path}')
        return None
    if not problem_rime_path.exists():
        logger.warning(f'PROBLEM not found in {base_path}')
        return None

    problem_toml = open(problem_toml_path, 'r').read()
    problem_rime = open(problem_rime_path, 'r').read()

    return problem_toml, problem_rime

def load_statement(base_path: Path, contest_id: str) -> str:
    statement_path = base_path / 'ss-out' / f'{contest_id}.md'
    if not statement_path.exists():
        logger.warning(f'Statement file not found in: {statement_path}')
    return open(statement_path, 'r').read()

def upload_statement_and_testcases(username: str, password: str):
    client = Client()
    client.login(username, password)

    for path in Path('./').glob('*'):
        if not path.is_dir() or not (path / 'PROBLEM').exists():
            continue
        
        logger.info(f'Processing for {path.name}')
        timer = time()
        make_zip(path)
        
        if (ret := load_setting_files(path)) is None:
            continue

        problem_toml, problem_rime = ret
        contest_id = parse_id_in_contest(problem_toml)
        statement = load_statement(path, contest_id)

        problem_id, problem, testcase_sets = load_problem(statement, problem_rime, problem_toml)

        client.upload_testcases(problem_id, f'{path.name}.zip')
        logger.info(f'Uploaded testcases')

        client.put_problem(problem_id, problem)
        logger.info(f'Updated problem statement')

        client.initialize_testcase_sets(problem_id)
        logger.info(f'Deleted all testcase_sets')
        
        for testcase_set in testcase_sets:
            testcase_ids = client.get_testcase_ids_regex(problem_id, testcase_set.regex)
            if testcase_set.is_sample() or testcase_set.is_all():
                client.put_testcase_set(problem_id, testcase_set)
            else:
                client.post_testcase_set(problem_id, testcase_set)
            testcase_set_id = client.get_testcase_set_id(problem_id, testcase_set.name)
            client.testcases_change_state_multiple(problem_id, testcase_ids, testcase_set_id)
            logger.info(f'Uploaded testcase_set {testcase_set.name}')
        
        testcases = client.get_testcases(problem_id)[1]
        for explanation_path in (path / 'tests').glob('*.md'):
            md = open(explanation_path, 'r').read()
            testcase_name = explanation_path.stem
            testcase_ids = [testcase.id for testcase in testcases if testcase.name == testcase_name]
            if len(testcase_ids) == 0:
                logger.warning(f'Testcase not found for {explanation_path.name}')
                continue
            testcase_id = testcase_ids[0]
            testcase = client.get_testcase(problem_id, testcase_id)
            testcase.explanation = md
            client.put_testcase(problem_id, testcase_id, testcase)
            logger.info(f'Uploaded explanation for {testcase_name}')
        
        logger.info(f'Finished processing for {path.name}, took {time() - timer:.2f}s')

if __name__ == '__main__':
    upload_statement_and_testcases(argv[1], argv[2])