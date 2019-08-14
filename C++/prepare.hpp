#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "split.hpp"
#include "types.hpp"

SequenceMap _build_sequence(std::string path, char sep);
void print_sequence_map(SequenceMap s);

IndexedSequenceMap _split_sequence(SequenceMap data, int length);
void print_indexed_sequence_map(IndexedSequenceMap s);

IndexedSequenceMap prepare_sequence(std::string path, int length, char sep);

void test_sequence();