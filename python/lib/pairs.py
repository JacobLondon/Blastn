from typing import Dict, List, DefaultDict
import tqdm
from collections import defaultdict
from .match import MatchStruct

"""
Internal
"""
class MatchSingleton:
    def __init__(self, word: str, dindex: int, qindex: int):
        """
        @brief: Hold both words from the pair, how long they are, and where they both are in the query and database.
        """
        self.word: str = word
        self.dindex: int = dindex
        self.qindex: int = qindex

    def __str__(self):
        return str(self.__dict__)
    
    def __repr__(self):
        return self.__str__()


class AdjacentPair:
    def __init__(self, word1: str, word2: str, dindex1: int, qindex1: int, dindex2: int, qindex2: int):
        """
        @brief: Hold both words from the pair, how long they are, and where they both are in the query and database.
        """
        self.word1: str = word1
        self.word2: str = word2
        self.length = len(self.word1)
        self.dindex1: int = dindex1
        self.qindex1: int = qindex1
        self.dindex2: int = dindex2
        self.qindex2: int = qindex2

    def __str__(self):
        return str(self.__dict__)
    
    def __repr__(self):
        return self.__str__()


def sort_and_append(flattened: List[MatchSingleton], result: list):

    ignore = []
    # appends to list of type adjacent pair

    for index1 in flattened:
        if index1 in ignore:
            continue
        for index2 in flattened:
            if index2 in ignore:
                continue
            
            if abs(index1.dindex - index2.dindex) >= len(index1.word):
                result.append(AdjacentPair(word1   = index1.word,       word2   = index2.word,
                                           dindex1 = index1.dindex, qindex1 = index1.qindex,
                                           dindex2 = index2.dindex, qindex2 = index2.qindex))
                break
            else:
                ignore.append(index2)
            ignore.append(index1)


"""
def sort_and_append(result: list, data_index: list, query_index: list, word: list):
    
    # sorts value of adjacent pairs relative to data indices 
    query_index = [query_index for _, query_index in sorted(zip(data_index, query_index))]
    word        = [word        for _, word        in sorted(zip(data_index, word))]
    data_index.sort()

    ignore = []
    # appends to list of type adjacent pair
    for index1, value1 in enumerate(data_index):
        if index1 in ignore:
            continue
        for index2, value2 in enumerate(data_index):
            if index2 in ignore:
                continue
            
            if abs(value2 - value1) >= len(word[index1]):
                result.append(AdjacentPair(word1   = word[index1],       word2   = word[index2],
                                           dindex1 = data_index[index1], qindex1 = query_index[index1],
                                           dindex2 = data_index[index2], qindex2 = query_index[index2]))
                break
            else:
                ignore.append(index2)
            ignore.append(index1)


def make_adjacent_pair(match_structs: List[MatchStruct]) -> List[AdjacentPair]:

    # initialize the lists we will use to store pertinent information
    result: List[AdjacentPair] = []
    
    # loop through matches 
    for match in match_structs:
        data_index = []
        query_index = []
        word = []
        for d_index in match.data_indices:
            for q_index in match.query_indices:
                data_index.append(d_index)
                query_index.append(q_index)
                word.append(match.word)
        sort_and_append(result, data_index, query_index, word)
    return result
"""

def flatten(match_structs: List[MatchStruct]):
    flat = []
    result: List[AdjacentPair] = []
    for match in match_structs:
        for dindex in match.data_indices:
            for qindex in match.query_indices:
                flat.append(MatchSingleton(match.word, dindex, qindex))
    flat.sort(key=lambda m: m.dindex)
    sort_and_append(flat, result)
    
    return result



"""
External
"""

def pair_filter(matches: Dict[str, Dict[str, List[MatchStruct]]],
                query: Dict[str, str]) -> Dict[str, Dict[str, List[AdjacentPair]]]:

    filtered_pairs: Dict[str, Dict[str, List[AdjacentPair]]] = {}
    
    for dname, queries in tqdm.tqdm(matches.items()):
        pairs = defaultdict(list)
        for qname, match_structs in queries.items():
            for pair in flatten(match_structs):
                #                                    distance threshold
                if abs(pair.dindex1 - pair.dindex2) <= len(query[qname]) - pair.length \
                    or abs(pair.qindex1 - pair.qindex2) >= pair.length \
                    or abs(pair.dindex1 - pair.dindex2) >= pair.length:
                    # only append if the pair isn't already recorded
                    if not any(pair.dindex1 == p.dindex1 for p in pairs[qname]):
                        pairs[qname].append(pair)
        if pairs:
            filtered_pairs[dname] = dict(pairs)
    return filtered_pairs
