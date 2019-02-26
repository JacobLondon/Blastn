
def split(query, length=11):
    num_words = len(query) - word_length + 1

    for index in range(num_words):
        yield(num_words[index:index + word_length])
