data = {
    "1" : "ATATATATATA",
    "2" : "TTTAAATTTAA",
    "3" : "AAAAAAAAAAA",
    "4" : "ATATAAAATTT"
}



def dust_algorithm (data, threshold):
    triplet = []
    for name, word in data.items():
        print (word)
        triplet = split(word, 3)
        print (split(word, 3))
        ignoreList = []
        occurranceScore = 0
        for i in range(0, len(triplet)-1):
            occurrance = 1
            if i not in ignoreList:
                k= i + 1
                while k < len(triplet) :
                    if triplet[i] == triplet[k] :
                        occurrance += 1
                        #print(occurrance, triplet[i])
                        ignoreList.append(k)
                    k += 1
                if occurrance > 1:
                    occurranceScore += (occurrance * (occurrance - 1) ) / 2
        score = occurranceScore / 8
        print (score)

    return
                    
#gotta clear if below threshold    

def split(iterable: iter, length: int) -> list:
    num_words = len(iterable) - length + 1
    words = []
    for i in range(num_words):
        words.append(iterable[i:i + length])
    return words


dust_algorithm(data, 11)
