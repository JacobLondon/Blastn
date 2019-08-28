from copy import copy
from typing import Dict, List

from smith_waterman import _smith_waterman
from pairs import AdjacentPair

class Extended:
    def __init__(self, dindex, extended_pair):
        self.dindex = dindex
        self.extended_pair = extended_pair

def extend_and_score(pair: AdjacentPair,
                     query: str,
                     data: str,
                     match: int,
                     mismatch: int,
                     gap: int,
                     minscore: int,
                     score=False,
                     printing=True) -> str:
    # find left-most indices
    dleftindex = min([pair.dindex1, pair.dindex2])
    qleftindex = min([pair.qindex1, pair.qindex2])
    drightindex = max([pair.dindex1, pair.dindex2])
    qrightindex = max([pair.qindex1, pair.qindex2])

    # build string
    qextended = query[qleftindex:qleftindex + pair.length]
    dextended = data[dleftindex:dleftindex + pair.length]

    # extend left
    qexindex = copy(qleftindex)
    dexindex = copy(dleftindex)
    while qexindex - 1 >= 0 and dexindex - 1 >= 0:
        qexindex -= 1
        dexindex -= 1
        qextended = query[qexindex] + qextended
        dextended = data[dexindex] + dextended
        if score:
            s = _smith_waterman(qextended, dextended, match=match, mismatch=mismatch, gap=gap, just_score=True)
            if s < minscore:
                return None
    
    # extend left pair to the right
    qexindex = qleftindex + pair.length - 1
    dexindex = dleftindex + pair.length - 1
    while qexindex + 1 < qrightindex:
        qexindex += 1
        dexindex += 1
        qextended = qextended + query[qexindex]
        dextended = dextended + data[dexindex]
    
    # extend right with gaps until qextended aligns with data
    while dexindex + 1 < drightindex:
        qexindex += 1
        dexindex += 1
        qextended = qextended + '-'
        dextended = dextended + data[dexindex]
    
    # append the right pair
    qextended = qextended + query[qrightindex:qrightindex + pair.length]
    dextended = dextended + data[drightindex:drightindex + pair.length]
    
    # extend right
    qexindex = qrightindex + pair.length - 1
    dexindex = drightindex + pair.length - 1
    while qexindex + 1 < len(query) and dexindex + 1 < len(data):
        qexindex += 1
        dexindex += 1
        qextended = qextended + query[qexindex]
        dextended = dextended + data[dexindex]
        if score:
            s = _smith_waterman(qextended, dextended, match=match, mismatch=mismatch, gap=gap, just_score=True)
            if s < minscore:
                return None
    
    if printing:
        print(f"Data Ext:\t{dextended}")
        print(f"Quer Ext:\t{qextended}")
    
    return qextended

def extend_filter(pairs: Dict[str, Dict[str, List[AdjacentPair]]],
                  minscore: int,
                  match: int,
                  mismatch: int,
                  gap: int) -> Dict[str, Dict[str, List[Extended]]]:
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
    print(qindex1, dindex1, qindex2, dindex2)
    print(f"Query:\t\t{query}")
    print(f"Data:\t\t{data}")
    result = extend_and_score(pair,
                             query,
                             data,
                             match=2,
                             mismatch=-1,
                             gap=-1,
                             minscore=6,
                             score=True,
                             printing=True)

