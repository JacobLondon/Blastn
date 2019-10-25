#include <algorithm> // sort
#include <cstdlib>   // rand

#include "sort.hpp"

namespace Blastn {

vector<HSP> sort(vector<HSP>& hsps)
{
    // sort by score
    std::sort(hsps.begin(), hsps.end(), [&](const HSP lhs, const HSP rhs)
    {
        return lhs.evalue < rhs.evalue;
    });
    
    return hsps;
}

} // Blastn