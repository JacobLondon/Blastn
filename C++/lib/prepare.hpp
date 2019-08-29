#pragma once
#include "../util/types.hpp"

Blastn::SequenceMap _build_sequence(std::string path, char sep);

Blastn::IndexedSequenceMap _split_sequence(Blastn::SequenceMap data, int32_t length);

Blastn::IndexedSequenceMap prepare_sequence(std::string path, int32_t length, char sep);
