#ifndef BLASTN_DUST_H
#define BLASTN_DUST_H

#include "../util/types.h"

float dust(char *word, uint32_t pattern_len);

IndexedSequenceMap *dust_filter(IndexedSequenceMap *data, float threshold, uint32_t pattern_len, uint32_t word_len);

#endif // BLASTN_DUST_H