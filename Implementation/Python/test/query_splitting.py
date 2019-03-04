'''
Given: a sequence of DNA, word length
Return: a list of words of length (given) from the sequence

Created by Alex Chan
March 4, 2019
'''
import random
#from sequence import generate_words, create_sequence

def create_sequence(length):
    letters = 'ACGT'
    sequence = ''

    for _ in range(length):
        sequence += random.choice(letters)

    return sequence

def query_split(query, length):
    num_words = len(query) - length + 1
    words = []
    indices = []
    for i in range(num_words): # number of words
        word = ''
        for j in range(i, i + length): # number of characters in query
            word += query[j]
        words.append(word)
        indices.append(i)
    return words, indices

def main():
    data = create_sequence(length=10000)
    query = create_sequence(length=25)
    #print('Dataset:\n', data)
    print('Query:\n', query)
    query = query_split(query, 11)
    print('Query:\n', query)

if __name__ == '__main__':
    main()
