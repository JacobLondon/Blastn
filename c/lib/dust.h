#ifndef BLASTN_DUST_H
#define BLASTN_DUST_H

#include "../util/types.h"

float dust(char *word, unsigned int pattern_len);

IndexedSequenceMap *dust_filter(IndexedSequenceMap *data, float threshold, unsigned int pattern_len, unsigned int word_len);

#endif // BLASTN_DUST_H