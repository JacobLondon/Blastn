#include <algorithm> // sort
#include <cstdlib>   // rand
#include "sort.hpp"
#include "smith_waterman.hpp"
#include "../util/display.hpp"

namespace Blastn {

FormattedSequenceMap sort_filter(FormattedSequenceMap& formatted_pairs)
{
    Progress progress{ formatted_pairs.size() };

    for (auto& qname_epairs : formatted_pairs) {
        // sort by score
        std::sort(qname_epairs.second.begin(), qname_epairs.second.end(), [&](const Formatted lhs, const Formatted rhs)
        {
            return lhs.score < rhs.score;
        });
        progress.update();
    }
    return formatted_pairs;
}

} // Blastn