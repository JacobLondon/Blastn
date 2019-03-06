"""
Author: Jacob London

Date Modified: March 4, 2019
"""

import random 

"""use to randomly create a sequence of a given length

@param length: size of sequence to generate
"""
def create_sequence(length):
    letters = 'ACGT'
    sequence = ''

    for _ in range(length):
        sequence += random.choice(letters)

    return sequence

"""use to randomly generate words to test searching for

@param amount: number of words to randomly generate
@param length: length of each word to generate
"""
def generate_words(amount, length):
    words = []
    for _ in range(amount):
        words.append(create_sequence(length))
    
    return words

"""Split words into a given length
Author: Alex Chan

@param query: a sequence of dna
@param length: length of words to split at
@return: tuple(list[sequences], list[indices])
"""
def split(query, length):
    num_words = len(query) - length + 1
    words = []
    # number of words
    for i in range(num_words):
        word = ''
        # number of characters in query
        for j in range(i, i + length):
            word += query[j]
        words.append(word)
    return words

"""Create a dictionary with a list of indices the word is found at
@param sequence: 'long dna sequence'
@param word_length: how long to make each possible word
@return: dict{'sequence': [indices]}
"""
def create_hash(sequence, word_length):
    words = split(sequence, word_length)
    table = {}

    # put all possible words into a dictionary
    for index in range(len(words)):
        if words[index] in table.keys():
            table[words[index]].append(index)
        else:
            table[words[index]] = [index]

    return table
