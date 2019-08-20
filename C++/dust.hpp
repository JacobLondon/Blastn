#pragma once
#include <string>
#include "types.hpp"

double _dust(std::string word, int pattern_len);

Blastn::IndexedSequenceMap dust_filter(Blastn::IndexedSequenceMap data, double threshold, int word_len, int triplet_len);

void test_dust();
