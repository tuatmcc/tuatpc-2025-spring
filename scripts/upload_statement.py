from lib.api import Client
from lib.parser import load_problem, parse_id_in_contest
from lib.logger import logger
from lib.util import load_problem_directories
from lib.problem import Problem

from upload_sample_explanations import upload_sample_explanations

from sys import argv
from pathlib import Path

def upload_statement(client: Client, problem_id: int, problem: Problem):    
    client.put_problem(problem_id, problem)
    logger.info(f'Updated problem statement, URL: {client.get_problem_url(problem_id)}')

if __name__ == '__main__':
    client = Client()
    client.login(argv[1], argv[2])

    problems = load_problem_directories(Path('./'))

    for problem_id, path, problem, testcase_sets in problems:
        upload_statement(client, problem_id, problem)
        upload_sample_explanations(client, problem_id, path / 'tests')
   