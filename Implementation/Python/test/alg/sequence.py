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
