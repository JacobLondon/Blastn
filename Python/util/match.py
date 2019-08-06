import os, sys, json, tqdm
from collections import defaultdict

thisfilepath = os.path.dirname(os.path.abspath(__file__))

"""
Find exact matches in the database given a sequence
"""

"""The details for what a match has, a word, data indices, and query indices
"""
class Match:
    def __init__(self, word: str=None, dindices: list=None, qindices: list=None):
        self.word: str = word
        self.data_indices: list = dindices
        self.query_indices: list = qindices
    
    def __str__(self):
        return "'" + self.word + "' @ query_indices = " + str(self.query_indices) + \
            ' and data_indices = ' + str(self.data_indices)

"""
query -> {qname : {word : [indices], word : [indices], ...}, qname : ..., }
data ->  {dname : {word : [indices], word : [indices], ...}, dname : ..., }

return exact_matches -> {dname : {qname : Match(word, dindices, qindices), ...}, ...}
"""
def match(query: dict, data: dict) -> dict:

    exact_matches = {}

    # traverse each data set
    for d_name, d_word_dict in tqdm.tqdm(data.items()):

        matches = defaultdict(list)

        # traverse each query set
        for q_name, q_word_dict in query.items():
            # traverse each word in the query set
            for q_word, q_indice_list in q_word_dict.items():
                # the current word in the query is also in the data set
                if q_word in d_word_dict.keys():
                    matches[q_name].append(Match(word=q_word, dindices=d_word_dict[q_word], qindices=q_indice_list))
        
        # record if there were matches found
        if matches:
            exact_matches[d_name] = dict(matches) 

    return exact_matches

"""

Test

"""

if __name__ == '__main__':
    
    dpath = '/data/data_small.fasta.json'
    qpath = '/data/query_small.fa.json'

    args = iter(sys.argv)

    try:
        for arg in args:
            if arg == '-d':
                dpath = next(args)
            elif arg == '-q':
                qpath = next(args)
            elif arg == 'help':
                print(
                """
                -d  \tjson dataset  \t(has default)
                -q  \tjson queries  \t(has default)
                """)
    except:
        print('Failure: invalid argument(s)')
        exit(-1)
    
    with open(thisfilepath + dpath, 'r') as d_json:
        data = json.load(d_json)
    with open(thisfilepath + qpath, 'r') as q_json:
        query = json.load(q_json)

    matches = match(query, data)

    # print the matches
    if matches is not None:
        for dataset, quers in matches.items():
            print(dataset, ':', sep='')
            for quer, matches in quers.items():
                print('\t', quer, ':', sep='')
                for match in matches:
                    print('\t', match)
