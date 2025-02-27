from typing import Dict, Optional

class Contest:
    def __init__(self, slug: Optional[str] = None, name: Optional[str] = None, kind: Optional[str] = None, start_at: Optional[str] = None, end_at: Optional[str] = None):
        self.slug = slug
        self.name = name
        self.kind = kind
        self.start_at = start_at
        self.end_at = end_at
    @classmethod
    def from_dict(cls, data: Optional[Dict[str, str]]) -> 'Contest':
        if data is None:
            return cls(None, None, None, None, None)
        return cls(
            slug=data.get('slug'),
            name=data.get('name'),
            kind=data.get('kind'),
            start_at=data.get('start_at'),
            end_at=data.get('end_at')
        )