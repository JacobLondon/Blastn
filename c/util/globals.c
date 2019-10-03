#include "globals.h"

const char BlastnGap = '-';
const char BlastnInvalid = '\0';

char BlastnSeperator = '>';       // .fa and .fasta line seperator
u32 BlastnSplitLength = 4;        // word length

s32 BlastnSwMinscore = 0;         // min smith waterman score before filtering out
s32 BlastnSwMatch = 2;            // smith waterman match score
s32 BlastnSwMismatch = -1;        // smith waterman mismatch score
s32 BlastnSwGap = -1;             // smith waterman gap score

f32 BlastnDustThreshold = 0.2f;   // dust threshold score before filtering out
u32 BlastnDustPatternLength = 3;  // length of patterns for dust to look for

char *BlastnOutput = "blastn_out.txt";
unsigned int BlastnMaxWidth = 256;
