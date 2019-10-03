#ifndef BLASTN_SPLIT_H
#define BLASTN_SPLIT_H

#include "../util/types.h"

Array(char *) *split_to_words(char *input, uint32_t split_length);

#endif // BLASTN_SPLIT_H