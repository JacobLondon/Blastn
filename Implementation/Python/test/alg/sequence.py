"""
Author: Jacob London

Date Modified: March 4, 2019
"""

import random, operator
from itertools import permutations
from functools import reduce

"""use to randomly create a sequence of a given length
"""
def create_sequence(length):
    letters = 'ACGT'
    sequence = ''

    for _ in range(length):
        sequence += random.choice(letters)

    return sequence

"""use to randomly generate words to test searching for
"""
def generate_words(amount, length):
    words = []
    for _ in range(amount):
        words.append(create_sequence(length))
    
    return words

"""Get all permutations of a word"""
def get_permutations(word):
    # return a set of all permutations to prevent duplicates
    return [''.join(p) for p in permutations(word)]

"""Get all permutations of all given words"""
def permute_words(words):
    # words are given [[]] of strings, get only inner layer
    return reduce(operator.add, [get_permutations(w) for w in words])

"""Split words into a given length"""
def split(query, length=11):
    num_words = len(query) - length + 1
    words = []
    indices = []

    for index in range(num_words):
        words.append(query[index:index + length])
        indices.append(index)

    return words, indices

"""Create a dictionary with a list of indices the word is found at"""
def create_hash(sequence, word_length):
    words, indices = split(sequence, word_length)
    table = {}
    for word, index in zip(words, indices):
        if word in table.keys():
            table[word].append(index)
        else:
            table[word] = [index]

    return table

"""Given a list(tuple('string', list(indices))),
reduce the list(indices) to be individual elements
in the output"""
def single_out_indices(matches):
    addtnl_indices = []
    first_indices = []
    for match in matches:
        # if there are multple indices
        indices = len(match[1])
        if indices > 1:
        # skip the first, keep it in position
            for i in range(1, indices):
                addtnl_indices.append((match[0], match[1][i]))

        # record the match's first index, temp1 holds all other indices
        first_indices.append((match[0], match[1][0]))

    # remove duplicate indices
    matches = first_indices
    matches.extend(addtnl_indices)

"""Find every nearby pair of candidate matches from a sorted list of matches"""
def get_candidates(matches, threshold):
    candidates = []

    # find all candidates from current until the threshold index distance is met
    for first in range(len(matches)):
        for second in range(first + 1, len(matches)):
            # at the end of all matches
            if first + second >= len(matches):
                break

            # get the indices for the current and next match
            index1 = matches[first][1][0]
            index2 = matches[second][1][0]

            # check if candidate is within the threshold
            if index2 - index1 < threshold:
                candidates.append((matches[first], matches[second]))
            # too far, go to next
            else:
                break

    return candidates
