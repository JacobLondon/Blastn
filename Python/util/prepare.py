
import os, sys, tqdm, json
from copy import copy
from collections import defaultdict

from .split import split

thisfilepath = os.path.dirname(os.path.abspath(__file__))

"""Given a .fa or .fasta file, turn it into .json format
where each sequence name maps to its sequence
"""
def build_sequence(path: str, sep: str='>') -> dict:
    seq_file = open(path, 'r')

    result = {} # {'sequence name' : 'sequence letters'}
    name = ''

    # put all sequence letters into a single string for each sequence
    for line in tqdm.tqdm(seq_file.readlines()):
        # a sequence name is found
        if line[0] == sep:
            # start after the seperator and remove newlines
            name = copy(line.rstrip('\n\r')[len(sep):])
            result[name] = []
        # sequence letters are found
        else:
            # remove newlines and append
            #print(line)
            result[name].append(line.rstrip('\n\r'))

    # change ['sequence'] -> 'sequence'
    for name, sequence in result.items():
        result[name] = ''.join(sequence)

    return result

"""Given a dictionary of 'name' : 'sequence', split
the sequence into words of a given length

Return {name : {word : [indices], word : [indices], ...}}
"""
def split_sequence(data: dict, length: int=11) -> dict:
    result = {}
    
    # traverse the sequence
    for name, sequence in data.items():
        # get all the words and find their indices in that data set
        words_with_indices = defaultdict(list)
        words = split(iterable=sequence, length=length)
        
        # map each word to all of their indices each time the word appears
        for i, word in enumerate(words):
            words_with_indices[word].append(i)
        
        result[name] = dict(words_with_indices)

    return result

"""Read in a .fa or .fasta file, split it by sequence
name and split the sequence into words of a given length
"""
def setup_data(path: str, length: int=11, sep: str='>', formatted: bool=False, write: bool=False) -> None:
    # read data to a dict 'name' : 'sequence'
    string_seq = build_sequence(path=path, sep=sep)
    # data -> 'name' : {'word' : [indices], 'word' : [indices], ...}
    split_seq = split_sequence(data=string_seq, length=length)

    # write to .json file
    if write:
        data_file = path + '.json'
        with open(data_file, 'w') as d_json:
            if formatted:
                json.dump(split_seq, d_json, indent=4, separators=(',', ': '))
            else:
                json.dump(split_seq, d_json)
        
    return split_seq

"""

Test

"""

if __name__ == '__main__':
    path = None
    length = 11
    sep = '>'
    formatted = False

    args = iter(sys.argv)

    try:
        for arg in args:
            if arg == '-p':
                path = next(args)
            elif arg == '-l':
                length = int(next(args))
            elif arg == '-s':
                sep = next(args)
            elif arg == '-f':
                formatted = True
            elif arg == 'help':
                print(
                """
                -p  \tfile path \t(expects *.fa or *.fasta)
                -l  \tlength    \t(has default)
                -s  \tseperator \t(has default)
                -f  \tformatted \t(has default)
                """)
                return
    except:
        print('Failure: invalid argument(s)')
        return

    setup_data(path=thisfilepath + path, length=length, sep=sep, formatted=formatted, write=True)
