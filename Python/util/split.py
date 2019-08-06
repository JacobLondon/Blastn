import sys

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
    
    iterable = 'ACGTACGTACGTACGTACGTACGT'
    length = 5

    args = iter(sys.argv)

    try:
        for arg in args:
            if arg == '-i':
                iterable = next(args)
            elif arg == '-l':
                length = int(next(args))
            elif arg == 'help':
                print(
                """
                -i  \tinput sequence\t(has default)
                -l  \tsplit length  \t(has default)
                """)
    except:
        print('Failure: invalid argument(s)')
        exit(-1)

    print(iterable)
    output = split(iterable=iterable, length=length)

    if output is not None:
        # pretty print the kmers
        for i, letter in enumerate(output):
            print(' ' * i, end='')
            print(letter, end='')
            print()
