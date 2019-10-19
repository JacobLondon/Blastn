#include "split.h"

Vector(char *) *split_to_words(char *input, unsigned int split_length)
{
    unsigned int num_words = strlen(input) - split_length + 1;
    vector(string) *words = vector_init(STRING, num_words);

    // reserve space, then load each split word
    for (unsigned int i = 0; i < num_words; i++) {

        string *word = string_init(split_length);

        for (unsigned int j = 0; j < split_length; j++)
            word->c_str[j] = input->c_str[i + j];
        
        // add the end of string char
        vector_append(words, word);
    }

    return words;
}
