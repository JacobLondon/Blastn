#ifndef BLASTN_GLOBALS_H
#define BLASTN_GLOBALS_H

#include "types.h"

extern const char BlastnGap;
extern const char BlastnInvalid;

extern char BlastnSeperator;          // .fa and .fasta line seperator
extern uint32_t BlastnSplitLength;         // word length

extern int32_t BlastnSwMinscore;          // min smith waterman score before filtering out
extern int32_t BlastnSwMatch;             // smith waterman match score
extern int32_t BlastnSwMismatch;          // smith waterman mismatch score
extern int32_t BlastnSwGap;               // smith waterman gap score

extern float BlastnDustThreshold;       // dust threshold score before filtering out
extern uint32_t BlastnDustPatternLength;   // length of patterns for dust to look for

extern char *BlastnOutput;
extern uint32_t BlastnMaxWidth;

#endif // BLASTN_GLOBALS_H