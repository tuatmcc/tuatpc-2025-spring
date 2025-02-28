import re
import tomllib
from .problem import Problem, ProblemConfig, ProblemStatement, Difficulty, TestCaseSet
from typing import Dict, Tuple, List
from .logger import logger

def find_first_match(content: str, pattern: re.Pattern, error_message: str) -> str:
    try:
        first_match = pattern.search(content).group(1)
    except AttributeError:
        raise ValueError(error_message)
    return first_match.strip()

def parse_statement(md_content: str) -> ProblemStatement:
    name_pattern = re.compile(r'# (.+)\n')
    statement_pattern = re.compile(r'## 問題文\n(.+?)##', re.DOTALL)
    constraints_pattern = re.compile(r'## 制約\n(.+?)##', re.DOTALL)
    partial_scores_pattern = re.compile(r'### 部分点\n(.+?)##', re.DOTALL)
    input_format_pattern = re.compile(r'## 入力\n(.+?)##', re.DOTALL)
    output_format_pattern_with_sample = re.compile(r'## 出力\n(.+?)##', re.DOTALL)
    output_format_pattern = re.compile(r'## 出力\n(.+?)$', re.DOTALL)
    try:
        name = find_first_match(md_content, name_pattern, '問題名が見つかりません。`# {問題名}` という行があるか確認してください。')
        statement = find_first_match(md_content, statement_pattern, '問題文が見つかりません。`## 問題文` という行があるか確認してください。')
        constraints = find_first_match(md_content, constraints_pattern, '制約が見つかりません。`## 制約` という行があるか確認してください。')
        input_format = find_first_match(md_content, input_format_pattern, '入力形式の説明が見つかりません。`## 入力` という行があるか確認してください。')
        if output_format_pattern_with_sample.search(md_content):
            output_format = find_first_match(md_content, output_format_pattern_with_sample, '出力形式の説明が見つかりません。`## 出力` という行があるか確認してください。')
        else:
            output_format = find_first_match(md_content, output_format_pattern, '出力形式の説明が見つかりません。`## 出力` という行があるか確認してください。')
    except AttributeError:
        raise ValueError('Invalid markdown format')

    partial_scores = ''
    if partial_scores_pattern.search(md_content):
        partial_scores = find_first_match(md_content, partial_scores_pattern, '部分点の説明が見つかりません。`### 部分点` という行があるか確認してください。')
    
    return ProblemStatement(
        name=name,
        statement=statement,
        constraints=constraints,
        input_format=input_format,
        output_format=output_format,
        partial_scores=partial_scores,
    )

# problem.toml
def parse_problem_config(problem_toml_content: str) -> Tuple[ProblemConfig, Dict[str, str]]:
    data = tomllib.loads(problem_toml_content)
    if 'mofe' not in data:
        raise ValueError('MOFE 用の設定が見つかりません。problem.toml に [mofe] というセクションがあるか確認してください。')
    if 'constraints' not in data:
        raise ValueError('制約の設定が見つかりません。problem.toml に [constraints] というセクションがあるか確認してください。')
    problem_config, constraints = data['mofe'], data['constraints']
    problem_config = ProblemConfig.from_dict(problem_config)
    for key, value in constraints.items():
        constraints[key] = str(value)
    return problem_config, constraints

def parse_id_in_contest(problem_toml_content: str) -> int:
    data = tomllib.loads(problem_toml_content)
    if 'id' not in data:
        raise ValueError('id が見つかりません。problem.toml に id というキーがあるか確認してください。')
    return data['id']

# PROBLEM
def parse_time_limit(PROBLEM_content: str) -> int:
    time_limit_pattern = re.compile(r'time_limit=*([\d.]+)')
    match = time_limit_pattern.search(PROBLEM_content)
    if match:
        time_limit_seconds = float(match.group(1))
        return int(time_limit_seconds * 1000)
    else:
        raise ValueError('time_limit not found in the file')

# statement.md + PROBLEM + problem.toml -> int, Problem, str
def load_problem(statement_content: str, problem_rime_content: str, problem_toml_content: str) -> Tuple[int, Problem, List[TestCaseSet]]:
    config, _ = parse_problem_config(problem_toml_content)
    testcase_sets = config.testcase_sets
    if config.execution_time_limit is None:
        execution_time_limit = parse_time_limit(problem_rime_content)
    else:
        execution_time_limit = config.execution_time_limit
    problem_id = config.problem_id
    problem_statement = parse_statement(statement_content)
    problem = Problem(
        name=problem_statement.name,
        difficulty=Difficulty(config.difficulty),
        statement=problem_statement.statement,
        constraints=problem_statement.constraints,
        input_format=problem_statement.input_format,
        output_format=problem_statement.output_format,
        partial_scores=problem_statement.partial_scores,
        execution_time_limit=execution_time_limit,
        submission_limit_1=config.submission_limit_1,
        submission_limit_2=config.submission_limit_2
    )
    return problem_id, problem, testcase_sets