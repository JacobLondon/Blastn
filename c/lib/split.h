#ifndef BLASTN_SPLIT_H
#define BLASTN_SPLIT_H

#include "../util/types.h"

Vector(char *) *split_to_words(char *input, unsigned int split_length);

#endif // BLASTN_SPLIT_H