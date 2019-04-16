import json, tqdm

"""
Find exact matches in the database given a sequence
"""

"""The details for what a match has, a word, data indices, and query indices
"""
class Match:
    def __init__(self, word: str=None, dindices: list=None, qindices: list=None):
        self.word = word
        self.data_indices = dindices
        self.query_indices = qindices
    
    def __str__(self):
        return self.word + ', data_indices: ' + str(self.data_indices) + ', query_indices: ' + str(self.query_indices)

"""Extracted function"""
def determine_match(query, d_word_dict, data, d_name, matches):
    # traverse each query set
    for q_name, q_word_dict in query.items():
        # traverse each word in the query set
        for q_word, q_indice_list in q_word_dict.items():
            # the current word in the query is also in the data set
            if q_word in d_word_dict.keys():
                matches[q_name] = Match(word=q_word, dindices=data[d_name][q_word], qindices=q_indice_list)

"""
query -> names : {word : [indices], word : [indices], ...}
data ->  names : {word : [indices], word : [indices], ...}

return exact_matches -> {dname : {qname : Match(word, dindices, qindices), ...}, ...}
"""
def match(query: dict, data: dict) -> dict:

    exact_matches = {}

    # traverse each data set
    for d_name, d_word_dict in tqdm.tqdm(data.items()):

        matches = {}
        # extracted function
        determine_match(query, d_word_dict, data, d_name, matches)
        # record if there were matches found
        if matches:
            exact_matches[d_name] = matches 

    return exact_matches

if __name__ == '__main__':
    with open('Gn-SRR7236689_contigs.fasta.json', 'r') as d_json:
        data = json.load(d_json)
    with open('SRR7236689--ARG830.fa.json', 'r') as q_json:
        query = json.load(q_json)

    matches = match(query, data)
    
    for ds, quers in matches.items():
        for q, match in quers.items():
            print(ds, q, match)
