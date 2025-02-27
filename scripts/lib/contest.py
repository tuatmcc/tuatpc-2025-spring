from typing import Dict

class Contest:
    def __init__(self, slug: str, name: str, kind: str, start_at: str, end_at: str):
        self.slug = slug
        self.name = name
        self.kind = kind
        self.start_at = start_at
        self.end_at = end_at
    @classmethod
    def from_dict(cls, data: Dict[str, str]) -> 'Contest':
        return cls(
            slug=data.get('slug'),
            name=data.get('name'),
            kind=data.get('kind'),
            start_at=data.get('start_at'),
            end_at=data.get('end_at')
        )