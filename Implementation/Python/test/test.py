
from alg import *
import random, time

dist_threshold = 40

start = time.time()

# create a database and a set of words to find
database = create_sequence(length=1000)
words = generate_words(amount=3, length=9)
# get all permutations of those words and look for them
perms = permute_words(words)
perm_time = time.time()

#matches = noregex_locate(perms, database)
matches = locate(perms, database)
match_time = time.time()

# matches: list(tuple('dna', list(indices)))

# sort the matches by their index
print('\nMatches:')
matches = sorted(matches.items(), key=lambda v: v[1])
sort_time = time.time()
"""for match in matches:
    print(str(matches[0][0]))"""
print(matches)

# find pairs of candidates which are close
candidates = []
for c in range(len(matches) - 1):

    first_indices = matches[c][1]
    second_indices = matches[c + 1][1]

    if second_indices[0] - first_indices[0] < dist_threshold:
        candidates.append((matches[c], matches[c + 1]))\

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
