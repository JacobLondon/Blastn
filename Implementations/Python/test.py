"""
File for unit testing
"""

from util import *

"""TEST CODE HERE"""
def main():

    """
    Example 1:
    You can use this to create sequences to
    test your program with.
    Create a sequence of length 10000 to use as a 'database' (Alden)
    Try larger values of length to test with larger dataset.
    """
    print('Example 1:')
    data = create_sequence(length=10000)
    query = create_sequence(length=20)
    print('Dataset:\n', data)
    print('Query:\n', query)

    """
    Example 2:
    Use a generator to create a bunch of random words
    so they can be used in low complexity filtering,
    and database searching
    """
    print('Example 2')
    words = generate_words(amount=30, length=11)
    for w in words:
        print(w)

if __name__ == '__main__':
    main()
