#ifndef _BLASTN_GLOBALS_H
#define _BLASTN_GLOBALS_H

#include "../tools/types.h"

void init_globals();

extern const char BlastnGap;
extern const char BlastnInvalid;

extern char BlastnSeperator;          // .fa and .fasta line seperator
extern u32 BlastnSplitLength;         // word length

extern s32 BlastnSwMinscore;          // min smith waterman score before filtering out
extern s32 BlastnSwMatch;             // smith waterman match score
extern s32 BlastnSwMismatch;          // smith waterman mismatch score
extern s32 BlastnSwGap;               // smith waterman gap score

extern f64 BlastnDustThreshold;       // dust threshold score before filtering out
extern u32 BlastnDustPatternLength;   // length of patterns for dust to look for

extern string *BlastnOutput;

#endif // _BLASTN_GLOBALS_H