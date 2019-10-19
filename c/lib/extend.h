#ifndef BLASTN_EXTEND_H
#define BLASTN_EXTEND_H

#include "../util/types.h"

Extended extend_and_score(
    AdjacentPair pair,
    char *query,
    char *data,
    signed int match,
    signed int mismatch,
    signed int gap,
    float ratio,
    bool score,
    bool printing
);

#endif // BLASTN_EXTEND_H