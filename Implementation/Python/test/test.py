
from alg import *
import random, time, cProfile

def main():

    dist_threshold = 40
    word_length = 9
    query_length = 14

    query = generate_words(amount=1, length=query_length)
    query = query[0]    # only one query, so just get first word
    words, i = split(query=query, length=word_length)
    database = create_sequence(length=1000)
    
    start = time.time()


    # create a database and a set of words to find
    database = create_hash(database, word_length)


    # get all permutations of those words and look for them
    perms = permute_words(words)
    perm_time = time.time()


    # matches: list(tuple('dna', list(indices)))
    # matches = locate(perms, database)
    # matches = regex_locate(perms, database)
    matches = locate_hash(perms, database)
    match_time = time.time()

    # sort the matches by their index
    print('\nMatches:')
    matches = sorted(matches.items(), key=lambda v: v[1])
    sort_time = time.time()
    print(matches)


    # find pairs of candidates which are close
    candidates = []
    for c in range(len(matches) - 1):

        first_indices = matches[c][1]
        second_indices = matches[c + 1][1]

        if second_indices[0] - first_indices[0] < dist_threshold:
            candidates.append((matches[c], matches[c + 1]))

    candidate_time = time.time()
    print('\nCandidates:')
    for c in candidates:
        print(c)


    end = time.time()
    total_time = end - start
    print('\nStats')
    print('Total time:', total_time)
    print('Permutation time:', perm_time - start, '\n', (perm_time - start) / total_time * 100)
    print('Match time:', match_time - perm_time, '\n', (match_time - perm_time) / total_time * 100)
    print('Sort time:', sort_time - match_time, '\n', (sort_time - match_time) / total_time * 100)
    print('Candidate time:', candidate_time - match_time, '\n', (candidate_time - match_time) / total_time * 100)
    print()

if __name__ == '__main__':
    #cProfile.run('main()')
    main()
