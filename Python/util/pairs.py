from typing import Dict, List

from match import MatchStruct

"""
Internal
"""

class AdjacentPair:
    def __init__(self, word1: str, word2: str, dindex1: int, qindex1: int, dindex2: int, qindex2: int):
        self.word1: str = word1
        self.word2: str = word2
        self.length = len(self.word1)
        self.dindex1: int = dindex1
        self.qindex1: int = qindex1
        self.dindex2: int = dindex2
        self.qindex2: int = qindex2

def _pair(matches: List[MatchStruct]) -> List[AdjacentPair]:
    result: List[AdjacentPair] = []

    # ...

    return result

"""
External
"""

def filter_pairs(matches: Dict[str, Dict[str, List[MatchStruct]]], query_len: int) -> Dict[str, Dict[str, List[AdjacentPair]]]:
    # close in the database (within query length of each other) and both in the same query
    pass

if __name__ == '__main__':
    pass
