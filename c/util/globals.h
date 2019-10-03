#ifndef BLASTN_GLOBALS_H
#define BLASTN_GLOBALS_H

#include "../tools/types.h"

extern const char BlastnGap;
extern const char BlastnInvalid;

extern char BlastnSeperator;          // .fa and .fasta line seperator
extern u32 BlastnSplitLength;         // word length

extern s32 BlastnSwMinscore;          // min smith waterman score before filtering out
extern s32 BlastnSwMatch;             // smith waterman match score
extern s32 BlastnSwMismatch;          // smith waterman mismatch score
extern s32 BlastnSwGap;               // smith waterman gap score

extern f32 BlastnDustThreshold;       // dust threshold score before filtering out
extern u32 BlastnDustPatternLength;   // length of patterns for dust to look for

extern char *BlastnOutput;
extern unsigned int BlastnMaxWidth;

#endif // BLASTN_GLOBALS_H