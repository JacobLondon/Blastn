from typing import Dict, List

from .extend import Extended
from .smith_waterman import smith_waterman

def sort_filter(extended_pairs: Dict[str, Dict[str, List[Extended]]],
                query: Dict[str, str],
                match: int,
                mismatch: int,
                gap: int) -> Dict[str, Dict[str, List[Extended]]]:
    for dname, queries in extended_pairs.items():
        for qname, epairs in queries.items():
            epairs.sort(key=lambda epair: smith_waterman(seq1=epair.extended_pair,
                                                         seq2=query[qname],
                                                         match=match,
                                                         mismatch=mismatch,
                                                         gap=gap,
                                                         just_score=True))
    return extended_pairs
