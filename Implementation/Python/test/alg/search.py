import re

"""Given a large set of letters and words, find all instances of
words (overlapping words too) given
Return a dictionary of words and their list of indices"""
def locate(words, database):
    lookup = {}     # dict lookup has (key=word, value=list of indices)
    
    for word in words:
        # look for all matches, including overlapping
        temp = [match.start()for match in re.finditer(f'(?={word})', database)]
        if len(temp) > 0:
            lookup[word] = temp

    return lookup

"""Same as above but without regex"""
def noregex_locate(words, database):
    lookup = {}

    # traverse all words
    for word in words:
        match_indices = []

        # look for in every pos in the database
        for index in range(len(database)):
            start = index
            found = False

            # align single letters
            for char in word:
                found = True
                # check next database char if there is no match
                if char != database[index]:
                    found = False
                    break

            # if it never broke out, it completed
            if found:
                match_indices.append(start - len(word))

        lookup[word] = match_indices
        # remove the entry if nothing was found
        if lookup[word] == []:
            del lookup[word]

    return lookup
