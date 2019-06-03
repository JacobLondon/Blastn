import split
import json
import os



#getting the file path for the json file
#change dusttestdata.txt to desired input json file
thisfilepath = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(thisfilepath, 'data\dusttestdata.txt')

#opening the file
with open (file_path) as json_file:
    data = json.load(json_file)

filtered_dictionary = {}
#Return {name : {word : [indices], word : [indices], ...}}

threshold_score = 2
#change value to filter words above score

#scores using a self similarity equation (refer to SDUST paper) and removes words under threshold
def dust_algorithm (data, threshold):
    #triplet tuple breaks words of 11 into subsequences of triplets(length 3)
    triplet = ()
    total_score = 0
    for key, values in data.items():
        for word, v in values.items():
            total_score = 0
            #triplet is a tuple of the 11-letter words split into subsequences of length 3 (triplet)
            triplet= tuple(split.split(word, 3))
            #ignore_list is used to avoid processing the same triplet twice in one word
            ignore_list = []
            for i, value in enumerate(triplet):
                if (value not in ignore_list):
                    occurrance = triplet.count(value)
                    occurrance_score = occurrance * (occurrance - 1) / 2
                    total_score += occurrance_score
                ignore_list.append(value)
            total_score = total_score / 8
            #words that score above the threshold will not be added to the filtered list
            if (total_score < threshold):
                filtered_dictionary[key] = {word : v}
    return (filtered_dictionary)

dust_algorithm(data, threshold_score)

#making filtered_dictionary a JSON file
file_path_filtered = os.path.join(thisfilepath, 'data\\filtereddictionary.txt')
with open (file_path_filtered, 'w') as filtered_json:
    json.dump(filtered_dictionary, filtered_json)