#ifndef BLASTN_SPLIT_H
#define BLASTN_SPLIT_H

#include "../tools/types.h"

vector(char *) *split_to_words(char *input, u32 split_length);

#endif // BLASTN_SPLIT_H