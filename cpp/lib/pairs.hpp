#pragma once
#include "../util/types.hpp"

namespace Blastn {

struct MatchSingleton {
    string word;
    u32 dindex;
    u32 qindex;
};

vector<AdjacentPair> pair(vector<MatchSingleton>& flattened, u32 query_len);

vector<AdjacentPair> flatten(vector<Match> matches, u32 query_len);

PairedSequenceMap pair_filter(MatchedSequenceMap matches, SequenceMap query);

} // Blastn