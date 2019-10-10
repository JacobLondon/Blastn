#include <algorithm>
#include "pairs.hpp"

#define ABS(value) ((s32)(value) < 0 ? (value) * -1 : (value))

void append(vector<MatchSingleton>& flattened, vector<AdjacentPair>& result, u32 query_len)
{
    for (u32 i = 0; i < flattened.size(); i++) {
        for (u32 j = i + 1; j < flattened.size(); j++) {
            // not overlapping
            if (ABS(((s32)flattened[i].dindex - (s32)flattened[j].dindex)) >= (s32)query_len
                // not too far apart
                && ABS(((s32)flattened[i].dindex - (s32)flattened[j].dindex)) <= (s32)query_len - (s32)flattened[i].word.size())
            {
                result.push_back(AdjacentPair {
                    flattened[i].word,   flattened[j].word,
                    flattened[i].dindex, flattened[i].qindex,
                    flattened[j].dindex, flattened[j].qindex
                });

                break;
            }
        }
    }
}

vector<AdjacentPair> flatten(vector<Match> matches, u32 query_len)
{
    vector<MatchSingleton> flattened;
    vector<AdjacentPair> result;

    for (auto& match : matches) {
        for (auto& dindex : match.data_indices) {
            for (auto& qindex : match.query_indices) {
                flattened.push_back(MatchSingleton {
                    match.word, dindex, qindex
                });
            }
        }
    }
    std::sort(flattened.begin(), flattened.end(), [&](const MatchSingleton lhs, const MatchSingleton rhs) {
        return lhs.dindex < rhs.dindex;
    });

    // result -> out argument
    append(flattened, result, query_len);
    return result;
}

Blastn::PairedSequenceMap pair_filter(Blastn::MatchedSequenceMap matches, Blastn::SequenceMap query)
{
    Blastn::PairedSequenceMap filtered_pairs;
    bool found = false;

    for (auto& dname_queries : matches) {
        Blastn::PairedMatchesMap pairs;
        for (auto& qname_matches : dname_queries.second) {
            for (auto& pair : flatten(qname_matches.second, query[qname_matches.first].size())) {
                if (ABS(((s32)pair.dindex1 - (s32)pair.dindex2)) <= (s32)query[qname_matches.first].size() - (s32)pair.length
                    || ABS((s32)pair.qindex1 - (s32)pair.qindex2) >= (s32)pair.length
                    || ABS((s32)pair.dindex1 - (s32)pair.dindex2 >= (s32)pair.length))
                {
                    // qname not created yet in pairs
                    if (pairs.find(qname_matches.first) == pairs.end())
                        pairs[qname_matches.first] = vector<AdjacentPair>{};

                    // check if the pair was recorded yet
                    found = false;
                    for (auto& p : pairs[qname_matches.first]) {
                        if (pair.dindex1 == p.dindex1) {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        pairs[qname_matches.first].push_back(pair);
                }
            }
        }
        if (!pairs.empty())
            filtered_pairs[dname_queries.first] = pairs;
    }
    return filtered_pairs;
}
