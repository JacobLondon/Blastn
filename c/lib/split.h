#ifndef _BLASTN_SPLIT_H
#define _BLASTN_SPLIT_H

#include "../tools/types.h"

vector(string) *split_to_words(string *input, u32 split_length);

#endif // _BLASTN_SPLIT_H