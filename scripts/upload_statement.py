from lib.api import Client
from lib.parser import load_problem, parse_id_in_contest
from lib.logger import logger
from lib.util import load_setting_files, load_statement

from sys import argv
from pathlib import Path

def upload_statement(username: str, password: str):
    client = Client()
    client.login(username, password)
    for path in Path('./').glob('*'):
        if not path.is_dir() or not (path / 'PROBLEM').exists():
            continue

        logger.info(f'Load files for {path.name}')

        if (ret := load_setting_files(path)) is None:
            continue

        problem_toml, problem_rime = ret
        contest_id = parse_id_in_contest(problem_toml)
        statement = load_statement(path, contest_id)

        problem_id, problem, _ = load_problem(statement, problem_rime, problem_toml)
        client.put_problem(problem_id, problem)
        logger.info(f'Updated problem statement, URL: {client.get_problem_url(problem_id)}')

if __name__ == '__main__':
    upload_statement(argv[1], argv[2])