#include <algorithm>
#include "pairs.hpp"

void append(vector<MatchSingleton>& flattened, vector<AdjacentPair>& result, u32 query_len)
{
    for (u32 i = 0; i < flattened.size(); i++) {
        for (u32 j = i + 1; j < flattened.size(); j++) {
            // not overlapping
            if (abs((int)(flattened[i].dindex - flattened[j].dindex)) >= query_len
                // not too far apart
                && abs((int)(flattened[i].dindex - flattened[j].dindex)) <= query_len - flattened[i].word.size())
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
        lhs.dindex < rhs.dindex;
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
                if (abs((int)(pair.dindex1 - pair.dindex2)) <= query[qname_matches.first].size() - pair.length
                    || abs((int)(pair.qindex1 - pair.qindex2) >= pair.length)
                    || abs((int)(pair.dindex1 - pair.dindex2 >= pair.length)))
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
