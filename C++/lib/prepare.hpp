#pragma once
#include "../util/types.hpp"

/**
 * @brief Given a .fa or .fasta file, seperate them into an unordered_map of names mapped to their data.
 * @param path The path to a .fa or .fasta file to build from.
 * @param sep The seperator character, denoting when a line contains a name.
 *            It should be the first character of the line.
 * @return The unordered_map of names and their data.
 */
Blastn::SequenceMap build_sequence(std::string path, char sep);
/**
 * @brief Split a built sequence into a data name mapped to split words mapped to each index it appears in the data.
 * @param data The SequenceMap to split.
 * @param length The size each word should be split at.
 * @return The data names mapped to split words mapped to their indices.
 */
Blastn::IndexedSequenceMap split_sequence(Blastn::SequenceMap data, int32_t length);
/**
 * @brief Build and split a .fa or .fasta sequence.
 * @param path The path to a .fa or .fasta file to build from.
 * @param length The size each word should be split at.
 * @param sep The seperator character, denoting when a line contains a name.
 *            It should be the first character of the line.
 * @return The build and split sequence.
 */
Blastn::IndexedSequenceMap prepare_sequence(std::string path, int32_t length, char sep);
