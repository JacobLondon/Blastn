import sys

def split_to_words(iterable: iter, length: int) -> list:
    """
    @brief: Split an iterable into all possible slices of given length \\
    @param iterable: A Python iterable to split into a list of words of length \\
    @param length:   The length of the words to extract from the iterable \\
    @return: A list of words of given length split from the iterable
    """
    num_words: int = len(iterable) - length + 1
    words: list = []
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
    output = split_to_words(iterable=iterable, length=length)

    if output is not None:
        # pretty print the kmers
        for i, letter in enumerate(output):
            print(' ' * i, end='')
            print(letter, end='')
            print()
