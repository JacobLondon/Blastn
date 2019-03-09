"""
Author: Jacob London

Date Modified: March 4, 2019
"""

import random, cProfile, timeit, sys

from util import *

def blastn():

    # control vars
    min_matches = 2
    score_threshold = 20
    dist_threshold = 40
    word_length = 7
    query_length = 14
    database_length = 10000

    random.seed(0)

    # start a time profiler to mark durations
    profiler = Profiler(printing=True)

    # generate starting values
    query = create_sequence(length=query_length)
    query_words = split(query=query, length=word_length)
    database = create_sequence(length=database_length)
    profiler.mark('startup')

    # score query_words here and remove those under the score threshold

    # create a database and a set of words to find
    database = create_hash(database, word_length)
    profiler.mark('preprocessing')

    # get all permutations of those words and look for them
    query_perms = permute_words(query_words)
    # complexity filtering of query_perms here
    # score query_perms here and remove those under the score threshold
    profiler.mark('permutation')

    # matches: list(tuple('sequence', list(indices)))
    query_matches = locate_hash(query_perms, database)
    query_matches = list(query_matches.items())
    print(query_matches)
    profiler.mark('matching')

    # make each value list have only 1 index, and append the others to the end
    query_matches = filter_min_occurrences(matches=query_matches, threshold=min_matches)
    #print(query_matches)
    query_matches = single_out_indices(matches=query_matches)
    quicksort(query_matches)
    profiler.mark('sorting')

    # find pairs of candidates which are close
    candidates = get_candidates(matches=query_matches, threshold=dist_threshold)
    profiler.mark('candidate')

    # extend with smith-waterman

    # don't record output printing time
    profiler.stop()

    # show matches/candidates
    print('\nQuery:', query)
    print('Matches:', len(query_matches))
    print('Candidates Pairs:', len(candidates))
    """print('\nMatches:', query_matches, sep='\n')
    print('\nCandidates:')
    for c in candidates:
        print(c)"""

    # show timing info
    profiler.display()

def cprofile_blastn():
    cProfile.run('blastn()')

def timeit_blastn(times=1):
    setup = 'from __main__ import blastn'
    stmt = 'blastn()'
    number = int(times)
    time = timeit.timeit(stmt=stmt, setup=setup, number=number)
    print('Average time:', time / number)
    # 1.0691106150800016 no generator
    # 1.0296630809562979 with generator

def main():

    if len(sys.argv) <= 1:
        blastn()
    elif sys.argv[1] == 'cprofile':
        cprofile_blastn()
    elif sys.argv[1] == 'timeit':
        if len(sys.argv) > 2:
            timeit_blastn(sys.argv[2])
        else:
            timeit_blastn()
    else:
        blastn()

if __name__ == '__main__':
    main()
