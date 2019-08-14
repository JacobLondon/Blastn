#pragma once

#include <string>
#include <unordered_map>
#include <vector>

/**
 * \brief Used in Smith Waterman for the matrices
 */
using Matrix = std::vector<std::vector<int>>;
/**
 * \brief Map sequence names to their sequence
 */
using SequenceMap = std::unordered_map<std::string, std::string>;
/**
 * \brief Map sequence names to all words mapped to a vector or indices where each word appears in its sequence
 */
using IndexedSequenceMap = std::unordered_map<std::string, std::unordered_map<std::string, std::vector<int>>>;
