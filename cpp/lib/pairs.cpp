#include <algorithm>
#include "pairs.hpp"
#include "../util/display.hpp"

namespace Blastn {

#define ABS(value) ((s32)(value) < 0 ? (value) * -1 : (value))

vector<AdjacentPair> pair(vector<MatchSingleton>& flattened, u32 query_len)
{
    vector<AdjacentPair> result;

    for (u32 i = 0; i < flattened.size(); i++) {
        for (u32 j = i + 1; j < flattened.size(); j++) {
            // not overlapping
            if (ABS(((s32)flattened[i].dindex - (s32)flattened[j].dindex)) >= (s32)flattened[i].word.size()
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
    return result;
}

vector<AdjacentPair> flatten(vector<Match> matches, u32 query_len)
{
    vector<MatchSingleton> flattened;

    for (auto& match : matches) {
        for (auto& dindex : match.subject_indices) {
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

    vector<AdjacentPair> result = pair(flattened, query_len);
    return result;
}

PairedSequenceMap pair_filter(MatchedSequenceMap matches, SequenceMap query)
{
    PairedSequenceMap filtered_pairs;
    Progress progress{ matches.size() };

    bool found = false;

    for (auto& dname_queries : matches) {
        PairedMatchesMap pairs;
        for (auto& qname_matches : dname_queries.second) {
            // qname not created yet in pairs
            if (pairs.find(qname_matches.first) == pairs.end())
                pairs[qname_matches.first] = vector<AdjacentPair>{};
            for (auto& pair : flatten(qname_matches.second, (u32)query[qname_matches.first].size())) {
                if (ABS((s32)pair.dindex1 - (s32)pair.dindex2) <= (s32)query[qname_matches.first].size() - (s32)pair.length
                    || ABS((s32)pair.qindex1 - (s32)pair.qindex2) >= (s32)pair.length
                    || ABS((s32)pair.dindex1 - (s32)pair.dindex2) >= (s32)pair.length)
                {
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

        progress.update();
    }
    return filtered_pairs;
}

} // Blastn