from enums import AggregateType
import re

class TestcaseSets:
    def __init__(self, testcase_set_id: int, name: str, regex_ptrn: re.Pattern, points: int, aggregate_type: AggregateType = AggregateType.ALL):
        self.name = name
        self.testcase_set_id = testcase_set_id
        self.regex_ptrn = regex_ptrn
        self.points = points
        self.aggregate_type = aggregate_type
    def is_sample(self):
        return 'sample' in self.name.lower()