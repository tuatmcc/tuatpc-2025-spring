from lib.api import Client
from lib.logger import logger
from lib.util import load_problem_directories
from lib.testcase import TestCaseSet

from pack_testcases import make_zip
from upload_sample_explanations import upload_sample_explanations

from typing import List
from sys import argv
from pathlib import Path

def upload_testcases(client: Client, problem_id: int, testcase_sets: List[TestCaseSet], problem_path: Path):
    logger.info(f'Upload testcases for {problem_path.name}')
    make_zip(problem_path)

    client.upload_testcases(problem_id, f'{problem_path.name}.zip')
    logger.info(f'Uploaded testcases')

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
    
    logger.info(f'Finished processing for {problem_path.name}')

if __name__ == '__main__':
    client = Client()
    client.login(argv[1], argv[2])

    problems = load_problem_directories(Path('./'))

    for problem_id, path, problem, testcase_sets in problems:
        upload_testcases(client, problem_id, testcase_sets, path)
        upload_sample_explanations(client, problem_id, path / 'tests')