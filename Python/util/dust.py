import json
import os
import tqdm
from typing import Dict, List

from .split import split_to_words

"""
External
"""

def dust(data: Dict[str, Dict[str, List[int]]], threshold: int) -> Dict[str, Dict[str, List[int]]]:
    """
    @brief: Perform the DUST algorithm on formatted data, and remove words which score below the threshold. \\
            It scores using a self similarity equation (refer to SDUST paper) and removes words under threshold. \\
    @param data:      The formatted data to perform DUST on \\
    @param threshold: The DUST score threshold to remove words at \\
    @return: The input dictionary without words which scored below the threshold
    """
    filtered_dictionary: Dict[str, Dict[str, List[int]]] = {}
    triplet: tuple = ()
    total_score: int = 0

    # breaks words of 11 into subsequences of tuple triplets (length 3)
    for key, values in tqdm.tqdm(data.items()):
        for word, v in values.items():
            total_score = 0
            # triplet is a tuple of the 11-letter words split into subsequences of length 3 (triplet)
            triplet= tuple(split_to_words(word, 3))
            # ignore_list is used to avoid processing the same triplet twice in one word
            ignore_list = []
            for value in triplet:
                if (value not in ignore_list):
                    occurrance = triplet.count(value)
                    occurrance_score = occurrance * (occurrance - 1) / 2
                    total_score += occurrance_score
                ignore_list.append(value)
            total_score = total_score / 8
            # words that score above the threshold will not be added to the filtered list
            if (total_score < threshold):
                filtered_dictionary[key] = {word: v}
    return filtered_dictionary

"""
Test
"""

if __name__ == '__main__':
    thisfilepath = os.path.dirname(os.path.abspath(__file__))

    test_data_path: str = 'data/dusttestdata.json'
    filtered_data_path: str = 'data/filtereddictionary.json'

    # opening the file
    with open(test_data_path) as json_file:
        data = json.load(json_file)

    # {name : {word : [indices], word : [indices], ...}}
    filtered_dictionary: Dict[str, Dict[str, List[int]]] = {}
    threshold_score = 2
    dust(data, threshold_score)

    # making filtered_dictionary a *.json file
    with open(filtered_data_path, 'w') as filtered_json:
        json.dump(filtered_dictionary, filtered_json)
