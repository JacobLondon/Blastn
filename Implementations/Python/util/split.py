
"""Split an iterable into all possible slices of given length"""
def split(iterable: iter, length: int) -> list:
    num_words = len(iterable) - length + 1
    words = []
    for i in range(num_words):
        words.append(iterable[i:i + length])
    
    return words

"""

Test

"""

if __name__ == '__main__':
    seq = 'ACGTACGTACGTACGTACGTACGT'
    length = 5

    output = split(iterable=seq, length=length)

    # pretty print the kmers
    print(seq)
    for i, letter in enumerate(output):
        print(' ' * i, end='')
        print(letter, end='')
        print('|' * (len(seq) - i - length), sep='', end='\n')

