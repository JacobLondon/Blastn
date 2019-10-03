#include "globals.h"

const char BlastnGap = '-';
const char BlastnInvalid = '\0';

char BlastnSeperator = '>';       // .fa and .fasta line seperator
uint32_t BlastnSplitLength = 4;        // word length

int32_t BlastnSwMinscore = 0;         // min smith waterman score before filtering out
int32_t BlastnSwMatch = 2;            // smith waterman match score
int32_t BlastnSwMismatch = -1;        // smith waterman mismatch score
int32_t BlastnSwGap = -1;             // smith waterman gap score

float BlastnDustThreshold = 0.2f;   // dust threshold score before filtering out
uint32_t BlastnDustPatternLength = 3;  // length of patterns for dust to look for

char *BlastnOutput = "blastn_out.txt";
unsigned int BlastnMaxWidth = 256;
