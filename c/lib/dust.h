#ifndef BLASTN_DUST_H
#define BLASTN_DUST_H

#include "../tools/types.h"

f32 dust(string word, u32 pattern_len);

indexed_sequence_map *dust_filter(indexed_sequence_map *data, f32 threshold, u32 pattern_len, u32 word_len);

#endif // BLASTN_DUST_H