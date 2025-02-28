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
    
    if old_problem.name != problem.name:
        logger.log(f'問題名が変更されました "{old_problem.name}" -> "{problem.name}"')
    if old_problem.difficulty != problem.difficulty:
        logger.log(f'難易度が変更されました "{old_problem.difficulty}" -> "{problem.difficulty}"')
    if old_problem.statement != problem.statement:
        logger.log(f'問題文が変更されました "{old_problem.statement}" -> "{problem.statement}"')
    if old_problem.constraints != problem.constraints:
        logger.log(f'制約が変更されました "{old_problem.constraints}" -> "{problem.constraints}"')
    if old_problem.partial_scores != problem.partial_scores:
        logger.log(f'部分点の説明が変更されました "{old_problem.partial_scores}" -> "{problem.partial_scores}"')
    if old_problem.input_format != problem.input_format:
        logger.log(f'入力の説明が変更されました "{old_problem.input_format}" -> "{problem.input_format}"')
    if old_problem.output_format != problem.output_format:
        logger.log(f'出力の説明が変更されました "{old_problem.output_format}" -> "{problem.output_format}"')

    logger.info(f'Updated problem statement, URL: {client.get_problem_url(problem_id)}')

if __name__ == '__main__':
    client = Client()
    client.login(argv[1], argv[2])

    problems = load_problem_directories(Path('./'))

    for problem_id, path, problem, testcase_sets in problems:
        upload_statement(client, problem_id, problem)
        upload_sample_explanations(client, problem_id, path / 'tests')
   