import sys, os
sys.path.append(os.path.abspath('../'))

from util import split

def main():
    seq = 'ACGTACGTACGTACGTACGTACGT'
    length = 5

    output = split(iterable=seq, length=length)

    # pretty print the kmers
    print(seq)
    for i, letter in enumerate(output):
        print(' ' * i, end='')
        print(letter, end='')
        print('|' * (len(seq) - i - length), sep='', end='\n')

if __name__ == '__main__':
    main()
