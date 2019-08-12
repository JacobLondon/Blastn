from typing import Dict, List

if __name__ == '__main__':
    from match import MatchStruct
else:
    from .match import MatchStruct

"""
Internal
"""

def _pair():
    pass

"""
External
"""

def filter_pairs(matches: Dict[str, Dict[str, List[MatchStruct]]], query_len: int) -> Dict[str, Dict[str, List[MatchStruct, MatchStruct]]]:
    # close in the database (within query length of each other) and both in the same query
    pass

if __name__ == '__main__':
    pass
