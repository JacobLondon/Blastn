"""
Requirements:
Python 3.6+
"""

import numpy as np

def mtch(alpha: str, beta: str, match: int, mismatch: int, gap: int) -> int:
    if alpha == beta:
        return match
    elif '-' == alpha or beta == '-':
        return gap
    else:
        return mismatch

def sw(seq1: str, seq2: str, printing: bool=False, match: int=2, mismatch: int=-1, gap: int=-1):

    m, n = len(seq1), len(seq2)

    score_mat = np.zeros((m + 1, n + 1))
    point_mat = np.zeros((m + 1, n + 1))

    max_score = 0
    max_i, max_j = 0, 0
    i, j = 0, 0

    # fill score matrix
    while i < m:
        i += 1; j = 0
        while j < n:
            j += 1
            scores = [
                # min acceptable score
                0,
                # left score
                score_mat[i - 1][j] + gap,
                # up score
                score_mat[i][j - 1] + gap,
                # diagnal score
                score_mat[i - 1][j - 1] + mtch(seq1[i - 1], seq2[j - 1], match, mismatch, gap)
            ]

            # index (point mat) corresponds to dir
            # value (score mat) corresponds to greatest score @ that index
            # https://stackoverflow.com/questions/6193498/pythonic-way-to-find-maximum-value-and-its-index-in-a-list
            point_mat[i][j], score_mat[i][j] = max(
                # scores -> enumerate where (index, scores[index]) per item
                # sort by item, but you also get the index it's at
                enumerate(scores), key=lambda e: e[1]
            )
            # record high score
            if score_mat[i][j] >= max_score:
                max_i, max_j = i, j
                max_score = score_mat[i][j]            

    aligned1, aligned2 = '', ''
    i, j = max_i, max_j

    while point_mat[i][j] != 0:
        # diagnal movement
        if point_mat[i][j] == 3:
            a1 = seq1[i - 1]
            a2 = seq2[j - 1]
            i -= 1; j -= 1
        # up movement
        elif point_mat[i][j] == 2:
            a1 = '-'
            a2 = seq2[j - 1]
            j -= 1
        # left movement
        elif point_mat[i][j] == 1:
            a1 = seq1[i - 1]
            a2 = '-'
            i -= 1

        # append the chars to the aligned build str
        aligned1 += a1
        aligned2 += a2

    # reverse the strings to forward order
    aligned1 = aligned1[::-1]
    aligned2 = aligned2[::-1]

    # build strings for the output
    output_alignment = ''
    similarity_percent = 0

    for a1, a2 in zip(aligned1, aligned2):
        # char in both, append to output str
        if a1 == a2:
            output_alignment += a1
            similarity_percent += 1
        # no match, maybe gap append gap to output str
        elif a1 != a2 and a1 != '-' and a2 != '-':
            output_alignment += '-'
        # gap in both
        elif a1 == '-' or a2 == '-':
            output_alignment += '-'

    # similarity to percent
    similarity_percent = similarity_percent / len(aligned1) * 100

    # user outputs
    if printing:
        print()
        print(f'Score matrix:\n{score_mat}')
        print()
        print(f'Point matrix:\n{point_mat}')
        print()

        print(f'Sequence 1: {seq1}')
        print(f'Sequence 2: {seq2}')
        print()

        print(f'Similarity: {similarity_percent}')
        print(f'Max score: {max_score}')

        print()
        print('Aligned1: ', aligned1)
        print('Aligned2: ', aligned2)
        print()
        print('  Output: ', output_alignment)

    return max_score

if __name__ == '__main__':
    seq1 = 'AGCACACA'
    seq2 = 'ACACACTA'
    sw(seq1, seq2, printing=True, match=2, mismatch=-1, gap=-1)
