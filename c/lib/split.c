#include "split.h"

Array(char *) *split_to_words(char *input, uint32_t split_length)
{
    uint32_t num_words = strlen(input) - split_length + 1;
    vector(string) *words = vector_init(STRING, num_words);

    // reserve space, then load each split word
    for (uint32_t i = 0; i < num_words; i++) {

        string *word = string_init(split_length);

        for (uint32_t j = 0; j < split_length; j++)
            word->c_str[j] = input->c_str[i + j];
        
        // add the end of string char
        vector_append(words, word);
    }

    return words;
}
