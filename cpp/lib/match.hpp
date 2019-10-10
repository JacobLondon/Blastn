#pragma once
#include "../util/types.hpp"

namespace Blastn {

/**
 * @brief Find all the exact matches of each query word in all data bases.
 * @return The exact matches with the indices of both the query and the data base.
 */
MatchedSequenceMap match_filter(IndexedSequenceMap& query, IndexedSequenceMap& data);

} // Blastn