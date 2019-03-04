import random

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


