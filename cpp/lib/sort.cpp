#include <algorithm> // sort
#include <cstdlib>   // rand
#include "sort.hpp"
#include "smith_waterman.hpp"
#include "../util/display.hpp"

namespace Blastn {

ExtendedSequenceMap sort_filter(ExtendedSequenceMap extended_pairs,
                                SequenceMap query,
                                s32 match,
                                s32 mismatch,
                                s32 gap)
{
    Progress progress { extended_pairs.size() };

    for (auto& dname_queries : extended_pairs) {
        for (auto& qname_epairs : dname_queries.second) {
            // sort by score
            std::sort(qname_epairs.second.begin(), qname_epairs.second.end(), [&](const Extended lhs, const Extended rhs)
            {
                return lhs.score < rhs.score;
            });
        }
        progress.update();
    }
    return extended_pairs;
}

} // Blastn