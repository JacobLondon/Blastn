#pragma once
#include "../util/types.hpp"

std::string _extend_and_score(AdjacentPair pair, std::string query, std::string data, int32_t match, int32_t mismatch, int32_t gap, int32_t minscore, bool score, bool printing);
