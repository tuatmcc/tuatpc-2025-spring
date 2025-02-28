from lib.api import Client
from lib.logger import logger
from lib.util import load_problem_directories
from lib.problem import Problem

from upload_sample_explanations import upload_sample_explanations

from sys import argv
from pathlib import Path

def upload_statement(client: Client, problem_id: int, problem: Problem):
    old_problem = client.get_problem(problem_id)
    client.put_problem(problem_id, problem)

    if old_problem.partial_scores is None:
        old_problem.partial_scores = ''

    if old_problem.name != problem.name:
        logger.info(f'問題名が変更されました "{old_problem.name}" -> "{problem.name}"')
    if old_problem.difficulty != problem.difficulty:
        logger.info(f'難易度が変更されました "{old_problem.difficulty}" -> "{problem.difficulty}"')
    if old_problem.statement != problem.statement:
        logger.info(f'問題文が変更されました\n"{old_problem.statement}"\n->\n"{problem.statement}"')
    if old_problem.constraints != problem.constraints:
        logger.info(f'制約が変更されました\n"{old_problem.constraints}"\n ->\n"{problem.constraints}"')
    if old_problem.partial_scores != problem.partial_scores:
        logger.info(f'部分点の説明が変更されました\n"{old_problem.partial_scores}"\n->\n"{problem.partial_scores}"')
    if old_problem.input_format != problem.input_format:
        logger.info(f'入力の説明が変更されました\n"{old_problem.input_format}"\n->\n"{problem.input_format}"')
    if old_problem.output_format != problem.output_format:
        logger.info(f'出力の説明が変更されました\n"{old_problem.output_format}"\n->\n"{problem.output_format}"')

    logger.info(f'Updated problem statement, URL: {client.get_problem_url(problem_id)}')

if __name__ == '__main__':
    client = Client()
    client.login(argv[1], argv[2])

    problems = load_problem_directories(Path('./'))

    for problem_id, path, problem, testcase_sets in problems:
        upload_statement(client, problem_id, problem)
        upload_sample_explanations(client, problem_id, path / 'tests')
   