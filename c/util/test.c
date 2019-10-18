#include "test.h"

void test_dust()
{

}

void test_extend()
{

}

void test_match()
{

}

void test_pairs()
{

}

void test_sequence()
{

}

void test_smith_waterman()
{

}

void test_sort()
{
    
}

void test_split()
{
    int split_length = 4;
    int word_length = 10;
    char* word = malloc(word_length * sizeof(char));
    strcpy(word, "0123456789");

    // call the function
    char** words = split_to_words(word, split_length);

    // print output
    int num_words = word_length - split_length + 1;
    for (int i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
}
