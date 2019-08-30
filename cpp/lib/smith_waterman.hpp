#pragma once
#include "../util/types.hpp"

// smith waterman
struct IValueTuple {
	int32_t index;
	int32_t value;
};

/**
 * @brief Return the greatest value and its number based on direction.
 */
inline IValueTuple max(int32_t left, int32_t up, int32_t diag);
/**
 * @brief given two different characters, pick a score depending on how they match.
 */
inline int32_t score_alignment(char alpha, char beta, int32_t match, int32_t mismatch, int32_t gap);
/**
 * @brief The smith waterman algorithm for aligning two sequences.
 * @param seq1 The first sequence to align.
 * @param seq2 The second sequence to align.
 * @param match The score when two characters are the same.
 * @param mismatch The score when two characters are not the same.
 * @param gap The score when there is a gap character.
 * @param just_score Indicate to exit the function early to only calculate the score.
 * @return The smith waterman score.
 */
int32_t smith_waterman(std::string seq1, std::string seq2, int32_t match, int32_t mismatch, int32_t gap, bool just_score);
/**
 * @brief Filter an IndexedSequenceMap with the smith waterman algorithm.
 * @param data The IndexedSequenceMap to filter.
 * @param minscore The minimum score a word can have before it is removed.
 * @param match The score when two characters are the same.
 * @param mismatch The score when two characters are not the same.
 * @param gap The score when there is a gap character.
 */
Blastn::IndexedSequenceMap smith_waterman_filter(Blastn::IndexedSequenceMap data, int32_t minscore, int32_t match, int32_t mismatch, int32_t gap);
