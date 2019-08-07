from .smithwaterman import smith_waterman

"""
Input dict format {name : {word : [indices], word : [indices], ...}}

Return the dict with low scoring words removed
"""
def remove_low_sw(data: dict, minscore: int, match: int, mismatch: int, gap: int):
    # traverse each sequence
    for name, sequence in data.items():
        # get the words from each element in each sequence
        for word in sequence.keys():
            if smith_waterman(word, word, match=match, mismatch=mismatch, gap=gap) < minscore:
                del data[name][word]
    return data
