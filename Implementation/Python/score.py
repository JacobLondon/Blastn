match = 5
mismatch = -4

"""
Note the following also works:
match = 2
mismatch = -3
"""

"""Calculate the score of the
nucleotide words indicated by
https://en.wikipedia.org/wiki/BLAST
under Algorithm section

"""
def score_words(word1, word2):
    global match, mismatch

    # make sure words are the same length
    assert len(word1) == len(word2)

    score = 0

    # calculate the score by comparing each letter
    for letter1, letter2 in zip(word1, word2):
        if letter1 == letter2:
            score += match
        else:
            score += mismatch

    return score
