#pragma once
#include "../util/types.hpp"

void sort_and_append(vector<AdjacentPair>& result, vector<u32> dindices, vector<u32> qindices, string word);

vector<AdjacentPair> make_adjacent_pair(vector<Match> matches);

Blastn::PairedSequenceMap pair_filter(Blastn::MatchedSequenceMap matches, Blastn::SequenceMap query);
