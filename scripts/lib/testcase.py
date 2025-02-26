from .enums import AggregateType
from typing import Optional
import re

class TestCaseSet:
    def __init__(self, name: str, points: int, aggregate_type: AggregateType = AggregateType.ALL, regex: Optional[re.Pattern] = None, testcase_set_id: Optional[int] = None):
        self.name = name
        self.regex = regex
        self.points = points
        self.aggregate_type = aggregate_type
        self.id = testcase_set_id
    
    def is_sample(self):
        return 'sample' in self.name.lower()
    
    def is_all(self):
        return 'all' in self.name.lower()

    @classmethod
    def from_dict(cls, data: dict) -> 'TestCaseSet':
        return cls(
            name=data['name'],
            regex=re.compile(data['regex']) if 'regex' in data else None,
            points=data['points'],
            aggregate_type=AggregateType(data.get('aggregate_type', AggregateType.ALL)),
            testcase_set_id=data.get('id', None)
        )
    def __repr__(self):
        return f'TestCaseSet(name={self.name}, regex={self.regex}, points={self.points}, aggregate_type={self.aggregate_type}, id={self.id})'

class TestCase:
    def __init__(self, name: str, testcase_id: int, testcase_sets : Optional[list[bool]] = None, testcase_input: Optional[str] = None, testcase_output: Optional[str] = None, explanation: Optional[None] = None):
        self.name = name
        self.id = testcase_id
        self.testcase_sets = testcase_sets
        self.input = testcase_input
        self.output = testcase_output
        self.explanation = explanation
    @classmethod
    def from_dict(cls, data: dict) -> 'TestCase':
        return cls(
            name=data['name'],
            testcase_id=data['id'],
            testcase_sets=data.get('testcase_sets'),
            testcase_input=data.get('input'),
            testcase_output=data.get('output'),
            explanation=data.get('explanation')
        )