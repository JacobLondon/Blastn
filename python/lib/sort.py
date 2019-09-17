from collections import defaultdict
from typing import Dict, List
import tqdm

import random

from .extend import Extended
from .smith_waterman import smith_waterman

class Sorted:
    def __init__(self, extended_pair, dindex, score):
        self.extended_pair = extended_pair
        self.dindex = dindex
        self.score = score

def sort_filter(extended_pairs: Dict[str, Dict[str, List[Extended]]],
                query: Dict[str, str],
                match: int,
                mismatch: int,
                gap: int) -> Dict[str, Dict[str, List[Sorted]]]:
    result: Dict[str, Dict[str, List[Sorted]]] = {}
    for dname, queries in tqdm.tqdm(extended_pairs.items()):
        temp = defaultdict(list)
        for qname, epairs in queries.items():
            for epair in epairs:
                temp[qname].append(Sorted(
                    epair.extended_pair,
                    epair.dindex,
                    random.randint(0, 100)))
                """smith_waterman(seq1=epair.extended_pair,
                                seq2=query[qname],
                                match=match,
                                mismatch=mismatch,
                                gap=gap,
                                just_score=True)))"""
            temp[qname].sort(key=lambda scored: scored.score)
        if temp:
            result[dname] = temp
    return result
