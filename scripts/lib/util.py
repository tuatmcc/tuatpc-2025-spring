from pathlib import Path
from typing import Optional, Tuple, List
from lib.logger import logger
from lib.parser import load_problem, parse_id_in_contest
from lib.problem import Problem
from lib.testcase import TestCaseSet

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

def load_problem_directories(base_path: Path) -> list[Tuple[int, Path, Problem, List[TestCaseSet]]]:
    problems = []
    for path in Path(base_path).glob('*'):
        if not path.is_dir() or not (path / 'PROBLEM').exists():
            continue

        logger.info(f'Load files for {path.name}')

        if (ret := load_setting_files(path)) is None:
            continue

        problem_toml, problem_rime = ret
        contest_id = parse_id_in_contest(problem_toml)
        statement = load_statement(path, contest_id)

        problem_id, problem, testcase_sets = load_problem(statement, problem_rime, problem_toml)
        problems.append((problem_id, path, problem, testcase_sets))
    logger.info(f'Loaded {len(problems)} problems')
    return problems