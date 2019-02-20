import random

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
def generate_words(amount, word_length):
    for _ in range(amount):
        yield(create_sequence(word_length))
