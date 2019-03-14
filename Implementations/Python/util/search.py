"""
Author: Jacob London

Date Modified: March 4, 2019
"""

"""Given a database where all possible words are sorted out,
get intersection of our words and all words that can exist

@param words: list['sequence', 'sequence', ...]
@param database: dict{'sequence': list[indices]}
@return: dict{'intersection sequences': [indices]}
"""
def locate_hash(words, database):
    lookup = {}
    for word in words:
        # if the word is in the database
        if word in database.keys():
            lookup[word] = database[word]
    
    return lookup
