from typing import Dict, List

from match import MatchStruct

"""
Internal
"""

class AdjacentPair:
    def __init__(self, word1: str, word2: str, dindex1: int, qindex1: int, dindex2: int, qindex2: int):
        """
        @brief: Hold both words from the pair, how long they are, and where they both are in the query and database.
        """
        self.word1: str = word1
        self.word2: str = word2
        self.length = len(self.word1)
        self.dindex1: int = dindex1
        self.qindex1: int = qindex1
        self.dindex2: int = dindex2
        self.qindex2: int = qindex2

def pair(matches: List[MatchStruct]) -> List[AdjacentPair]:
    result: List[AdjacentPair] = []

    # ...

    return result

"""
External
"""

def pair_filter(matches: Dict[str, Dict[str, List[MatchStruct]]], query_len: int) -> Dict[str, Dict[str, List[AdjacentPair]]]:
    # close in the database (within query length of each other) and both in the same query
    # look into collections.OrderedDict -> convert 'dict' to 'OrderedDict' then sort
    result = {}
    for dname, queries in matches.items():
        result[dname] = {}
        for qname, matches in queries.items():
            # two items: same data base, same query
            result[qname] = pair(matches)
