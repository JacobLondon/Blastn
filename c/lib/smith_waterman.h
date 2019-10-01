#ifndef BLASTN_SMITH_WATERMAN_H
#define BLASTN_SMITH_WATERMAN_H

#include "../tools/types.h"

s32 smith_waterman(string seq1, string seq2, s32 match, s32 mismatch, s32 gap);

indexed_sequence_map *smith_waterman_filter(indexed_sequence_map *data, s32 minscore, s32 match, s32 mismatch, s32 gap);

#endif // BLASTN_SMITH_WATERMAN_H