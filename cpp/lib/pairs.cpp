#include "pairs.hpp"

struct MatchSingleton {
    string word;
    u32 dindex;
    u32 qindex;
};

void sort_and_append(vector<AdjacentPair>& result, vector<u32> dindices, vector<u32> qindices, string word)
{
    

    dict<u32, u32> ignore;
    for (u32 i = 0; i < dindices.size(); i++) {
        if (ignore.find(dindices[i]) != ignore.end())
            continue;
        for (u32 j = 0; j < dindices.size(); j++) {
            if (ignore.find(dindices[j]) != ignore.end())
                continue;

            if (abs((int)(dindices[j] - dindices[i])) >= word.size()) {
                // TODO: finish converting pairs.py
            }
        }
    }
}

vector<AdjacentPair> make_adjacent_pair(vector<Match> matches)
{
    vector<AdjacentPair> result;

    for (auto& match : matches) {
        sort_and_append(result, match.data_indices, match.query_indices, match.word);
    }
    return result;
}

Blastn::PairedSequenceMap pair_filter(Blastn::MatchedSequenceMap matches, Blastn::SequenceMap query)
{
    Blastn::PairedSequenceMap filtered_pairs;
    bool found = false;

    for (auto& dname_queries : matches) {
        Blastn::PairedMatchesMap pairs;
        for (auto& qname_matches : dname_queries.second) {
            for (auto& pair : make_adjacent_pair(qname_matches.second)) {
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
