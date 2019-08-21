from copy import copy

#from smith_waterman import _smith_waterman

def extend_and_score() -> None:
    pass
"""
2 adjacent pairs
LEFT (lesser index)
    extend leftward one at a time and score
RIGHT (greater index)
    extend rightward one at a time and score
MIDDLE
    fill with gap characters
"""

if __name__ == '__main__':
    # inputs
    query = 'GTCTCAACTG'
    qindexl = 5
    data  = 'GTCTCAACTG'
    dindexl = 5
    match = 'AAC'
    # helper
    qindexr = qindexl + len(match)
    dindexr = dindexl + len(match)
    qlen = len(query)
    dlen = len(data)
    extended_match = copy(match)

    assert len(data) >= len(query)
    assert len(extended_match) < len(query)

    # right and left extension amount
    rext = 0
    lext = 1
    rsuccess = False
    lsuccess = False

    # extend the match right then left until it is the length of its query
    while len(extended_match) != qlen:
        lsuccess = False
        rsuccess = False
        # extend right, check OOB
        if qindexr + rext < qlen and dindexr + rext < dlen:
            extended_match = extended_match + data[qindexr + rext]
            rext += 1
            rsuccess = True
        # extend left, check OOB
        if qindexl - lext >= 0 and dindexl - lext >= 0:
            extended_match = data[qindexl - lext] + extended_match
            lext += 1
            lsuccess = True
        # neither left nor right extended
        if not any([lsuccess, rsuccess]):
            break
    
    print(extended_match)