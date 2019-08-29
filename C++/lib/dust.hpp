#pragma once
#include "../util/types.hpp"

float64_t _dust(std::string word, int32_t pattern_len);

Blastn::IndexedSequenceMap dust_filter(Blastn::IndexedSequenceMap data, float64_t threshold, int32_t word_len, int32_t pattern_len);
