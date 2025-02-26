import re
import tomllib
from problem import Problem, ProblemConfig, ProblemStatement, Difficulty
from typing import Dict, Tuple
import logging

logger = logging.getLogger(__name__)

def parse_statement(md_content: str) -> ProblemStatement:
    name_pattern = re.compile(r'# (.+)\n')
    statement_pattern = re.compile(r'## 問題文\n(.+?)##', re.DOTALL)
    constraints_pattern = re.compile(r'## 制約\n(.+?)##', re.DOTALL)
    partial_scores_pattern = re.compile(r'### 部分点\n(.+?)##', re.DOTALL)
    input_format_pattern = re.compile(r'## 入力\n(.+?)##', re.DOTALL)
    output_format_pattern_with_sample = re.compile(r'## 出力\n(.+?)##', re.DOTALL)
    output_format_pattern = re.compile(r'## 出力\n(.+?)$', re.DOTALL)
    try:
        name = name_pattern.search(md_content).group(1).strip()
        statement = statement_pattern.search(md_content).group(1).strip()
        constraints = constraints_pattern.search(md_content).group(1).strip()
        input_format = input_format_pattern.search(md_content).group(1).strip()
        if output_format_pattern_with_sample.search(md_content):
            output_format = output_format_pattern_with_sample.search(md_content).group(1).strip()
        else:
            output_format = output_format_pattern.search(md_content).group(1).strip()
    except AttributeError:
        raise ValueError('Invalid markdown format')
    
    partial_scores = ''
    if partial_scores_pattern.search(md_content):
        partial_scores = partial_scores_pattern.search(md_content).group(1)
    
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
    problem_config, constraints = data['mofe'], data['constraints']
    problem_config = ProblemConfig.from_dict(problem_config)
    for key, value in constraints.items():
        constraints[key] = str(value)
    return problem_config, constraints

# PROBLEM
def parse_time_limit(PROBLEM_content: str) -> int:
    time_limit_pattern = re.compile(r'time_limit=*([\d.]+)')
    match = time_limit_pattern.search(PROBLEM_content)
    if match:
        time_limit_seconds = float(match.group(1))
        return int(time_limit_seconds * 1000)
    else:
        raise ValueError('time_limit not found in the file')

def embed_constraints(md_content: str, parameters: dict[str, str]) -> str:
    print(parameters.items())
    for key, value in parameters.items():
        md_content = md_content.replace(f'{{@constraints.{key}}}', str(value))
    return md_content

# statement.md + PROBLEM + problem.toml -> int, Problem, constraints, str
def load_problem(statement_content: str, problem_rime_content: str, problem_toml_content: str) -> Tuple[int, Problem, Dict[str, str], str]:
    config, constraints = parse_problem_config(problem_toml_content)
    execution_time_limit = parse_time_limit(problem_rime_content)
    problem_id = config.problem_id
    embedded_statement = embed_constraints(statement_content, constraints)
    problem_statement = parse_statement(embedded_statement)
    problem = Problem(
        name=problem_statement.name,
        difficulty=Difficulty(config.difficulty),
        statement=embedded_statement,
        constraints=problem_statement.constraints,
        input_format=problem_statement.input_format,
        output_format=problem_statement.output_format,
        partial_scores=problem_statement.partial_scores,
        execution_time_limit=execution_time_limit,
        submission_limit_1=config.submission_limit_1,
        submission_limit_2=config.submission_limit_2
    )
    return problem_id, problem, constraints, embedded_statement