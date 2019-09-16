#pragma once
#include "../util/types.hpp"

/**
 * @brief The Dust algorithm for scoring words based on sub patterns of self-similarity.
 * @param word The word to score based on its self-similarity.
 * @param pattern_len The lengths of sections in word to see how self similar they are.
 * @reteurn The Dust score.
 */
f64 dust(string word, u32 pattern_len);

/**
 * @brief Filter the IndexedSequenceMap using the dust algorithm.
 * @param data The format of the data to be filtered.
 * @param threshold Dust scores less than this threshold will be removed from data.
 * @param word_len The length of the words in data.
 * @param pattern_len The length of the patterns to look for in each word.
 * @return A copy of the IndexedSequenceMap with low scoring words removed.
 */
Blastn::IndexedSequenceMap dust_filter(Blastn::IndexedSequenceMap& data, f64 threshold, u32 pattern_len, u32 word_len);
