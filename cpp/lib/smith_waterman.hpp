#pragma once

#include "../util/types.hpp"

namespace Blastn {

// smith waterman
struct Greatest {
    u32 index;
    s32 value;
};

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
s32 smith_waterman(string& seq1, string& seq2, s32 match, s32 mismatch, s32 gap, bool just_score);

s32 smith_waterman_no_preserve(string& seq1, string& seq2, s32 match, s32 mismatch, s32 gap);
s32 smith_waterman_preserve(char *seq1, char *seq2, s32 match, s32 mismatch, s32 gap, s32 *shm, size_t cols, size_t rows);

s32 smith_waterman_mt(string& seq1, string& seq2, s32 match, s32 mismatch, s32 gap);

s32 smith_waterman_fgpa(char *seq1, char *seq2, s32 match, s32 mismatch, s32 gap, size_t cols, size_t rows);

} // Blastn