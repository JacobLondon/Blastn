
from alg import *
import random

dist_threshold = 40

# create a database and a set of words to find
database = create_sequence(length=1000)
words = generate_words(amount=3, length=7)
# get all permutations of those words and look for them
perms = permute_words(words)

#matches = noregex_locate(perms, database)
matches = locate(perms, database)

# matches: list(tuple('dna', list(indices)))

# sort the matches by their index
print('\nMatches:')
matches = sorted(matches.items(), key=lambda v: v[1])
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

print('\nCandidates:')
for c in candidates:
    print(c)
