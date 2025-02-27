from lib.api import Client
from lib.parser import load_problem, parse_id_in_contest
from sys import argv
from pathlib import Path
from pack_testcases import make_zip

if __name__ == '__main__':
    client = Client()
    client.login(argv[1], argv[2])

    for path in Path('./').glob('*'):
        if not path.is_dir() or not (path / 'PROBLEM').exists():
            continue
        make_zip(path)
        problem_toml = open(path / 'problem.toml', 'r').read()
        problem_rime = open(path / 'PROBLEM', 'r').read()
        statement_path = path / 'ss-out' / f'{parse_id_in_contest(problem_toml)}.md'
        statement = open(statement_path, 'r').read()
        problem_id, problem, constraints, testcase_sets = load_problem(statement, problem_rime, problem_toml)

        client.put_problem(problem_id, problem)
        client.upload_testcases(problem_id, f'{path.name}.zip')
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