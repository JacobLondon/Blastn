#include <string.h> // strlen
#include <stdlib.h> // malloc
#include <stdio.h>  // printf

char **split_to_words(char *input, int split_length);

char **split_to_words(char *input, int split_length)
{
    int i, j, k;
    int num_words = strlen(input) - split_length + 1;
    char **words = malloc(num_words * sizeof(char *));

    // reserve space, then load each split word
    for (i = 0; i < num_words; i++) {

        // reserve space for the word followed by '\0'
        words[i] = malloc((split_length + 1) * sizeof(char));

        // copy the next word into the newly malloc'ed spot
        for (j = 0; j < split_length; j++)
            words[i][j] = input[i + j];
        
        // add the end of string char
        words[i][j] = '\0';
    }

    return words;
}

static int tsplit()
{
    int split_length = 4;
    int word_length = 10;
    char *word = malloc(word_length * sizeof(char));
    strcpy(word, "0123456789");

    // call the function
    char **words = split_to_words(word, split_length);

    // print output
    int num_words = word_length - split_length + 1;
    for (int i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
}
