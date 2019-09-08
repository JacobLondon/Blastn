
#include "globals.h"
#include "../tools/string.h"

const char BlastnGap = '-';
const char BlastnInvalid = '\0';

void init_globals()
{
    char BlastnSeperator = '>';       // .fa and .fasta line seperator
    u32 BlastnSplitLength = 4;        // word length

    s32 BlastnSwMinscore = 0;         // min smith waterman score before filtering out
    s32 BlastnSwMatch = 2;            // smith waterman match score
    s32 BlastnSwMismatch = -1;        // smith waterman mismatch score
    s32 BlastnSwGap = -1;             // smith waterman gap score

    f64 BlastnDustThreshold = 0.2f;   // dust threshold score before filtering out
    u32 BlastnDustPatternLength = 3;  // length of patterns for dust to look for

    string *BlastnOutput = string_init("blastn_out.txt");
}
