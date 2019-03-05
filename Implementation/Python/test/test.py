"""
Author: Jacob London

Date Modified: March 4, 2019
"""

import random, cProfile

from alg import *
from profiler import Profiler

def main():

    # control vars
    dist_threshold = 40
    word_length = 9
    query_length = 14
    database_length = 1000

    # start a time profiler to mark durations
    profiler = Profiler()

    # generate starting values
    query = generate_words(amount=1, length=query_length)
    query = query[0]    # only one query, so just get first word
    words, i = split(query=query, length=word_length)
    database = create_sequence(length=database_length)

    # create a database and a set of words to find
    database = create_hash(database, word_length)
    profiler.mark('preprocessing')

    # get all permutations of those words and look for them
    perms = permute_words(words)
    profiler.mark('permutation')

    # matches: list(tuple('dna', list(indices)))
    matches = locate_hash(perms, database)
    matches = list(matches.items())
    profiler.mark('matching')

    # make each value list have only 1 index, and append the others to the end
    matches = single_out_indices(matches)
    print('presort\n', matches)
    matches = sorted(matches, key=lambda v: v[1])
    #matches = sorted(matches, key=lambda v: v[0][1])
    profiler.mark('sorting')

    # find pairs of candidates which are close
    candidates = get_candidates(matches=matches, threshold=dist_threshold)
    profiler.mark('candidate')

    # don't record output printing time
    profiler.stop()

    # show matches/candidates
    print('\nMatches:')
    print(matches)
    print('\nCandidates:')
    for c in candidates:
        print(c)

    # show timing info
    profiler.display()

if __name__ == '__main__':
    #cProfile.run('main()')
    main()
