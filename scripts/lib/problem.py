from .enums import Difficulty
from typing import Dict, Any, List, Optional
from .constants import DEFAULT_SUBMISSION_LIMIT_1, DEFAULT_SUBMISSION_LIMIT_2, DEFAULT_EXECUTION_TIME_LIMIT, DEFAULT_DIFFICULTY
from .testcase import TestCaseSet
from .contest import Contest

class ProblemConfig:
    def __init__(self, problem_id: int, difficulty: Difficulty, testcase_sets: List[TestCaseSet], execution_time_limit: Optional[int],submission_limit_1: int = DEFAULT_SUBMISSION_LIMIT_1, submission_limit_2: int = DEFAULT_SUBMISSION_LIMIT_2):
        self.problem_id = problem_id
        self.difficulty = difficulty
        self.testcase_sets = testcase_sets
        self.execution_time_limit = execution_time_limit
        self.submission_limit_1 = submission_limit_1
        self.submission_limit_2 = submission_limit_2
    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'ProblemConfig':
        return cls(
            problem_id=data['problem_id'],
            difficulty=Difficulty(data['difficulty']),
            testcase_sets=[TestCaseSet.from_dict(value[0] | {'name' : key}) for key, value in data['testcase_sets'].items()],
            execution_time_limit=data.get('execution_time_limit', None),
            submission_limit_1=data.get('submission_limit_1', DEFAULT_SUBMISSION_LIMIT_1),
            submission_limit_2=data.get('submission_limit_2', DEFAULT_SUBMISSION_LIMIT_2)
        )
    def __repr__(self):
        return f'ProblemConfig(problem_id={self.problem_id}, difficulty={self.difficulty}, testcase_sets={self.testcase_sets}, execution_time_limit={self.execution_time_limit}, submission_limit_1={self.submission_limit_1}, submission_limit_2={self.submission_limit_2})'

class ProblemStatement:
    def __init__(self, name: str, statement: str, constraints: str, input_format: str, output_format: str, partial_scores: str = ''):
        self.name = name
        self.statement = statement
        self.constraints = constraints
        self.partial_scores = partial_scores
        self.input_format = input_format
        self.output_format = output_format

class Problem:
    def __init__(self, name: str, difficulty: Difficulty, statement: str, constraints: str, input_format: str, output_format: str, partial_scores: str = '', execution_time_limit: int = DEFAULT_EXECUTION_TIME_LIMIT, submission_limit_1: int = DEFAULT_SUBMISSION_LIMIT_1, submission_limit_2: int = DEFAULT_SUBMISSION_LIMIT_2, slug: Optional[str] = None, contest: Optional[Contest] = None):
        self.name = name
        self.difficulty = difficulty
        self.constraints = constraints
        self.partial_scores = partial_scores
        self.input_format = input_format
        self.output_format = output_format
        self.statement = statement
        self.execution_time_limit = execution_time_limit
        self.submission_limit_1 = submission_limit_1
        self.submission_limit_2 = submission_limit_2
        self.slug = slug
        self.contest = contest

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> 'Problem':
        return cls(
            name=data['name'],
            difficulty=Difficulty(data['difficulty']),
            constraints=data['constraints'],
            partial_scores=data['partial_scores'],
            input_format=data['input_format'],
            output_format=data['output_format'],
            statement=data['statement'],
            execution_time_limit=data['execution_time_limit'],
            submission_limit_1=data['submission_limit_1'],
            submission_limit_2=data['submission_limit_2'],
            slug=data.get('slug', None),
            contest=Contest.from_dict(data['contest']) if 'contest' in data else None
        )

    def to_dict(self) -> Dict[str, Any]:
        return {
            'name': self.name,
            'difficulty': self.difficulty.value,
            'constraints': self.constraints,
            'input_format': self.input_format,
            'output_format': self.output_format,
            'partial_scores': self.partial_scores if self.partial_scores != '' else None,
            'statement': self.statement,
            'execution_time_limit': self.execution_time_limit,
            'submission_limit_1': self.submission_limit_1,
            'submission_limit_2': self.submission_limit_2
        }