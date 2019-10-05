#include <stdio.h>
#include "packed.h"

unsigned int pack(const char *word, unsigned char length)
{
    PackedWord result = { 0 };
    unsigned char i;

    for (i = 0; i < length; i++) {
        switch (word[i]) {
        case 'A':
            result.word = (result.word << 2) | (A_CONV);
            break;
        case 'C':
            result.word = (result.word << 2) | (C_CONV);
            break;
        case 'G':
            result.word = (result.word << 2) | (G_CONV);
            break;
        case 'T':
            result.word = (result.word << 2) | (T_CONV);
            break;
        default:
            fprintf(stderr, "Pack error: Unexpected character: '%c'\n", word[i]);
            exit(-1);
        }
    }

    // i can be no larger than 4 bits
    result.word = (result.word << 4) | i;
    // no gaps (4), DC (2)
    result.word <<= 6;

    return result.word;
}
