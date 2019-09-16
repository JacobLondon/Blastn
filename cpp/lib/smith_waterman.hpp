#pragma once
#include "../util/types.hpp"

// smith waterman
struct IValueTuple {
	u32 index;
	s32 value;
};

/**
 * @brief Return the greatest value and its number based on direction.
 */
inline IValueTuple max(s32 left, s32 up, s32 diag);
/**
 * @brief given two different characters, pick a score depending on how they match.
 */
inline s32 score_alignment(char alpha, char beta, s32 match, s32 mismatch, s32 gap);
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
s32 smith_waterman(string seq1, string seq2, s32 match, s32 mismatch, s32 gap, bool just_score);
/**
 * @brief Filter an IndexedSequenceMap with the smith waterman algorithm.
 * @param data The IndexedSequenceMap to filter.
 * @param minscore The minimum score a word can have before it is removed.
 * @param match The score when two characters are the same.
 * @param mismatch The score when two characters are not the same.
 * @param gap The score when there is a gap character.
 */
Blastn::IndexedSequenceMap smith_waterman_filter(Blastn::IndexedSequenceMap& data, s32 minscore, s32 match, s32 mismatch, s32 gap);
