import random, operator
from itertools import permutations
from functools import reduce

"""Hmayak, Simon:
use to randomly create a sequence of a given length
"""
def create_sequence(length):
    letters = 'ATGC'
    sequence = ''

    for _ in range(length):
        sequence += random.choice(letters)

    return sequence

"""Alden, Siva:
use to randomly generate words to test searching for
"""
def generate_words(amount, length):
    for _ in range(amount):
        yield(create_sequence(length))

"""Get all permutations of a word"""
def get_permutations(word):
    # return a set of all permutations to prevent duplicates
    return [''.join(p) for p in permutations(word)]

"""Get all permutations of all given words"""
def permute_words(words):
    # words are given [[]] of strings, get only inner layer
    return reduce(operator.add, [get_permutations(w) for w in words])
