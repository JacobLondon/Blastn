#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "types.hpp"

Blastn::SequenceMap _build_sequence(std::string path, char sep);
void print(Blastn::SequenceMap s);

Blastn::IndexedSequenceMap _split_sequence(Blastn::SequenceMap data, int length);
void print(Blastn::IndexedSequenceMap s);

Blastn::IndexedSequenceMap prepare_sequence(std::string path, int length, char sep);

void test_sequence();