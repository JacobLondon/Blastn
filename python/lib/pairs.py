from typing import Dict, List, DefaultDict
from collections import defaultdict
from .match import MatchStruct

"""
Internal
"""

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

def sort_and_append(result: list, data_index: list, query_index: list, db_name: list, query_name: list, word: list):
    
    #sorts value of adjacent pairs relative to data indices 
    query_index = [query_index for _,query_index in sorted(zip(data_index, query_index))]
    query_name = [query_name for _,query_name in sorted(zip(data_index, query_name))]
    word = [word for _,word in sorted(zip(data_index, word))]
    db_name = [db_name for _,db_name in sorted(zip(data_index, db_name))]
    data_index.sort()

    ignore_list = []
    #appends to list of type adjacent pair
    for index in range(len(data_index)):
        if index not in ignore_list:
            for index2 in range(len(data_index)):
                if index2 not in ignore_list:
                    if (abs(index2-index) >= len(word[index])):
                        result.append(AdjacentPair(word1 = word[index], 
                                                    word2 = word[index2], 
                                                    dindex1 = data_index[index], 
                                                    qindex1= query_index[index], 
                                                    dindex2 = data_index[index2], 
                                                    qindex2 = query_index[index2]))
                        break
                    else:
                        ignore_list.append(index2)
                    ignore_list.append(index)
                
    return result

def make_adjacent_pair(match_structs: List[MatchStruct], dname: str, qname: str) -> List[AdjacentPair]:

    #initialize the lists we will use to store pertinent information
    result: List[AdjacentPair] = []
    data_index = []
    query_index = []
    db_name = []
    query_name = []
    word = []

    #used to process the last index in case it has a matching adjacent pair
    last_entry_valid = False

    #loop through matches 
    for match in match_structs:
        last_entry_valid = False

        #for the first iteration
        if (len(db_name)==0):
            db_name.append(dname)
            for d_index in match.data_indices:
                for q_index in match.query_indices:
                    data_index.append(d_index)
                    query_index.append(q_index)
                    query_name.append(qname)
                    word.append(match.word)

        #checks to see if subsequent entries are in the same database and query
        #as they could be used to make adjacent matching pairs
        elif (dname == db_name[len(db_name)-1] and qname == query_name[len(query_name)-1]):
            for d_index in match.data_indices:
                for q_index in match.query_indices:
                    data_index.append(d_index)
                    query_index.append(q_index)
                    query_name.append(qname)
                    word.append(match.word)
            last_entry_valid = True

        #if we reach an entry that has different database as preceding entries
        #we order our lists that contain data related to our adjacent matching pairs
        #relative to the database indices and append it to our list containing adjacent matching pairs
        else:
            result = sort_and_append(result, data_index, query_index, db_name, query_name, word)

            #clear the lists and append the current entry to the list
            db_name.clear()
            data_index.clear()
            query_index.clear()
            query_name.clear()
            word.clear()
            db_name.append(dname)
            for d_index in match.data_indices:
                for q_index in match.query_indices:
                    data_index.append(d_index)
                    query_index.append(q_index)
                    query_name.append(qname)
                    word.append(match.word)

    #used in case the final entry is part of a matching adjacent pair
    if (last_entry_valid):
        result = sort_and_append(result, data_index, query_index, db_name, query_name, word)

    return result

"""
External
"""

def pair_filter(matches: Dict[str, Dict[str, List[MatchStruct]]],
                query: Dict[str, str]) -> Dict[str, Dict[str, List[AdjacentPair]]]:
    filtered_pairs: Dict[str, Dict[str, List[AdjacentPair]]] = {}
    result = []
    for dname, queries in matches.items():
        pairs: DefaultDict[str, List[AdjacentPair]] = defaultdict(list)
        for qname, match_structs in queries.items():
            result = make_adjacent_pair(match_structs, dname, qname)
            for pair in result:
                #                                    distance threshold
                if (abs(pair.dindex1-pair.dindex2) > len(query[qname]) - pair.length \
                    or abs(pair.qindex1-pair.qindex2) < pair.length \
                    or abs(pair.dindex1-pair.dindex2) < pair.length):
                    pass
                else:
                    pairs[qname].append(pair)
        if pairs:
            filtered_pairs[dname] = dict(pairs)
    return filtered_pairs
