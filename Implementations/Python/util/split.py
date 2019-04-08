
"""Split an iterable into all possible slices of given length"""
def split(iterable, length):
    num_words = len(iterable) - length + 1
    words = []
    for i in range(num_words):
        words.append(iterable[i:i + length])
    
    return words
