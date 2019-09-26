#include <algorithm> // sort
#include <cstdlib>   // rand
#include "sort.hpp"
#include "smith_waterman.hpp"


Blastn::SortedSequenceMap sort_filter(Blastn::ExtendedSequenceMap extended_pairs,
                                      Blastn::SequenceMap query,
                                      s32 match,
                                      s32 mismatch,
                                      s32 gap)
{
    Blastn::SortedSequenceMap result;
    for (auto& dname_queries : extended_pairs) {
        Blastn::SortedPairsMap temp;
        for (auto& qname_epairs : dname_queries.second) {
            if (temp.find(qname_epairs.first) == temp.end())
                temp[qname_epairs.first] = vector<Sorted>{};
            for (auto& epair : qname_epairs.second) {
                temp[qname_epairs.first].push_back(Sorted{
                        epair.extended_pair,
                        epair.dindex,
                        epair.qindex,
                        rand() % 100
                        //smith_waterman(epair.extended_pair, query[qname_epairs.first], match, mismatch, gap, true);
                    });
            }
            // sort by score
            std::sort(temp[qname_epairs.first].begin(), temp[qname_epairs.first].end(), [&](const Sorted lhs, const Sorted rhs)
            {
                return lhs.score < rhs.score;
            });
        }
        if (!temp.empty())
            result[dname_queries.first] = temp;
    }
    return result;
}