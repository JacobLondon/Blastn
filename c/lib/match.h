#ifndef BLASTN_MATCH_H
#define BLASTN_MATCH_H

#include "../util/types.h"

MatchedSequenceMap match_filter(IndexedSequenceMap query, IndexedSequenceMap& data);

#endif // BLASTN_MATCH_H