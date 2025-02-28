from lib.api import Client
from lib.logger import logger
from pathlib import Path

def upload_sample_explanations(client: Client, problem_id: int, samples_path: Path):
    testcases = client.get_testcases(problem_id)[1]
    for explanation_path in samples_path.glob('*.md'):
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
        logger.info(f'Uploaded sample explanation for {testcase_name}')