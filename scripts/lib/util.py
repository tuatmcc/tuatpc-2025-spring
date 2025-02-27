from pathlib import Path
from typing import Optional, Tuple
from lib.logger import logger

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