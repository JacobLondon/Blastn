#pragma once

#include <string>
#include <vector>
#include "types.hpp"

/**
 * \brief Find all the exact matches of each query word in all data bases
 * \return The exact matches with the indices of both the query and the data base
 */
Blastn::MatchedSequenceMap match_filter(Blastn::IndexedSequenceMap query, Blastn::IndexedSequenceMap data);

void print(Blastn::MatchedSequenceMap);
//void test_match();