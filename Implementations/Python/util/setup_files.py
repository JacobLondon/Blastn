
import os, tqdm, json
from copy import copy

from split import split

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
            result[name].append(line.rstrip('\n\r'))

    # change ['sequence'] -> 'sequence'
    for name, sequence in result.items():
        result[name] = sequence[0]

    return result

"""Given a dictionary of 'name' : 'sequence', split
the sequence into words of a given length
"""
def split_sequence(data: dict, length: int=11) -> dict:
    result = {}
    
    # traverse the sequence
    for name, sequence in data.items():
        result[name] = split(iterable=sequence, length=length)

    return result

"""Read in a .fa or .fasta file, split it by sequence
name and split the sequence into words of a given length
"""
def setup_data(path: str, length: int=11, sep: str='>') -> None:
    # read data to a dict 'name' : 'sequence'
    string_seq = build_sequence(path, sep=sep)
    # data -> 'name' : ['word', 'word', ...]
    split_seq = split_sequence(string_seq, length=length)

    # write to .json file
    data_file = thisfilepath + os.sep + path + '.json'
    with open(data_file, 'w') as d_json:
        json.dump(split_seq, d_json, indent=0, separators=(',', ': '))

if __name__ == '__main__':
    f_in = 'SRR7236689--ARG830.fa'
    #f_in = 'Gn-SRR7236689_contigs.fasta'
    setup_data(f_in)
        