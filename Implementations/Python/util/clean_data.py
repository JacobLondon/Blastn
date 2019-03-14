"""
Author: Jacob London

Date Modified: March 14, 2019

Clean the data once it has been found.
"""

"""Given a list of matches, remove items where
list(indices) length is less than then threshold.

@param matches: list(tuple('sequence', list(indices)))
@param threshold: min length for list(indices) to be
@return: list(tuple('sequence', list(indices, length >= threshold)))
"""
def filter_min_occurrences(matches, threshold):
    filtered_out = []
    for match in matches:
        if len(match[1]) >= threshold:
            filtered_out.append(match)
    
    return filtered_out

"""Given a list(tuple('sequence', list(indices))),
reduce the list(indices) to be individual elements
in the output"""
def single_out_indices(matches):
    singled_out = []
    addtnl_indices = []
    first_indices = []
    for match in matches:
        # if there are multple indices
        indices = len(match[1])
        if indices > 1:
            # skip the first, keep it in position
            for i in range(1, indices):
                addtnl_indices.append((match[0], match[1][i]))

        # record the match's first index, temp1 holds all other indices
        first_indices.append((match[0], match[1][0]))

    # remove duplicate indices
    singled_out = first_indices
    singled_out.extend(addtnl_indices)
    return singled_out

"""Find every nearby pair of candidate matches from a sorted list of matches"""
def get_candidates(matches, threshold):
    candidates = []

    # find all candidates from current until the threshold index distance is met
    for first in range(len(matches)):
        # start at 1 to not match with itself
        for second in range(1, len(matches)):
            # at the end of all matches
            if first + second >= len(matches):
                break

            # get the indices for the current and next match
            index1 = matches[first][1]
            index2 = matches[first + second][1]

            # check if candidate is within the threshold
            if index2 - index1 < threshold:
                candidates.append((matches[first], matches[first + second]))
            # too far, go to next
            else:
                break

    return candidates
