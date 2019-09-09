#include "split.h"
#include "../tools/vector.h"
#include "../tools/string.h"

vector(string) *split_to_words(string *input, u32 split_length)
{
    u32 num_words = input->size - split_length + 1;
    vector(string) words = *vector_init(STRING, num_words);

    // reserve space, then load each split word
    for (u32 i = 0; i < num_words; i++) {

        string word = *string_init(split_length);

        for (u32 j = 0; j < split_length; j++)
            word.c_str[j] = input->c_str[i + j];
        
        // add the end of string char
        vector_append(&words, &word);
    }

    return &words;
}
