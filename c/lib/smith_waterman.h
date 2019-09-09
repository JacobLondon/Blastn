#ifndef _BLASTN_SMITH_WATERMAN_H
#define _BLASTN_SMITH_WATERMAN_H

#include "../tools/types.h"

s32 smith_waterman(string seq1, string seq2, s32 match, s32 mismatch, s32 gap);

#endif // _BLASTN_SMITH_WATERMAN_H