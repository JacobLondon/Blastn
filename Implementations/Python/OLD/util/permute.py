'''
Given: a sequence of DNA, word length
Return: a list of words of length (given) from the sequence

Author: Jacob London
Date Modified: March 5, 2019
'''
import operator

from functools import reduce
from itertools import permutations
from math import factorial

"""Get all permutations of a word"""
def get_permutations(word):
    # return a set of all permutations to prevent duplicates
    return [''.join(p) for p in permutations(word)]

"""Get all permutations of all given words"""
def permute_words(words):
    # words are given [[]] of strings, get only inner layer
    return reduce(operator.add, [get_permutations(w) for w in words])

"""Same as permute_words but acts as a generator instead"""
def permute_words_generator(words):
    length = factorial(len(words[0]))
    for word in words:
        perms = permutations(word)
        for _ in range(length):
            yield ''.join(next(perms))
