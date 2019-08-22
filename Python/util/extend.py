from copy import copy
from typing import Dict, List

from smith_waterman import _smith_waterman
from pairs import AdjacentPair

def extend_and_score(pair: AdjacentPair,
                     query: str,
                     data: str,
                     match: int,
                     mismatch: int,
                     gap: int,
                     minscore: int,
                     score=False,
                     format=True) -> str:
    # find left-most indices
    dleftindex = min([pair.dindex1, pair.dindex2])
    qleftindex = min([pair.qindex1, pair.qindex2])
    drightindex = max([pair.dindex1, pair.dindex2])
    qrightindex = max([pair.qindex1, pair.qindex2])

    # build string
    extended = query[qleftindex:qleftindex + pair.length]

    # extend left
    qexindex = copy(qleftindex)
    dexindex = copy(dleftindex)
    while qexindex - 1 >= 0 and dexindex - 1 >= 0:
        qexindex -= 1
        dexindex -= 1
        extended = data[dexindex] + extended
        if score:
            # score with itself
            s = _smith_waterman(extended, extended, match=match, mismatch=mismatch, gap=gap, just_score=True)
            if s < minscore:
                return None

    # pad left with spaces for pretty printing
    if format:
        extended = (' ' * dexindex) + extended
    
    # extend left pair to the right
    qexindex = qleftindex + pair.length - 1
    dexindex = dleftindex + pair.length - 1
    while qexindex + 1 < qrightindex:
        qexindex += 1
        dexindex += 1
        extended = extended + data[dexindex]
    
    # extend right with gaps until extended aligns with data
    while dexindex + 1 < drightindex:
        qexindex += 1
        dexindex += 1
        extended = extended + '-'
    
    # append the right pair
    extended = extended + query[qrightindex:qrightindex + pair.length]
    
    # extend right
    qexindex = qrightindex + pair.length - 1
    dexindex = drightindex + pair.length - 1
    while qexindex + 1 < len(query) and dexindex + 1 < len(data):
        qexindex += 1
        dexindex += 1
        extended = extended + data[dexindex]
        if score:
            # score with itself
            s = _smith_waterman(extended, extended, match=match, mismatch=mismatch, gap=gap, just_score=True)
            if s < minscore:
                return None
    
    return extended

def extend_filter(pairs: Dict[str, Dict[str, List[AdjacentPair]]],
                  minscore: int,
                  match: int,
                  mismatch: int,
                  gap: int) -> Dict[str, Dict[str, List[str]]]:
    pass

"""
2 adjacent pairs
LEFT (lesser index)
    extend leftward one at a time and score
MIDDLE
    fill with gap characters
RIGHT (greater index)
    extend rightward one at a time and score
"""

if __name__ == '__main__':
    # inputs
    query = 'GTCTGAACTGAGC'
    data  = 'AGTCTGATGACTGGGGAACTCGA'
    word1 = 'TC'
    word2 = 'CT'
    qindex1 = query.find(word1)
    dindex1 = data.find(word1)
    qindex2 = query.find(word2, qindex1 + len(word1))
    dindex2 = data.find(word2, dindex1 + len(word1))
    pair = AdjacentPair(word1=word1,
                        word2=word2,
                        qindex1=qindex1,
                        dindex1=dindex1,
                        qindex2=qindex2,
                        dindex2=dindex2)
    
    result = extend_and_score(pair,
                             query,
                             data,
                             match=2,
                             mismatch=-1,
                             gap=-1,
                             minscore=6,
                             score=True)

    print(f"Query:  {query}")
    print(f"Data:   {data}")
    print(f"Extend: {result}")
