#pragma once
#include <string>
#include "types.hpp"

std::string _extend_and_score(AdjacentPair pair, std::string query, std::string data, int match, int mismatch, int gap, int minscore, bool score, bool printing);

void test_extend();
