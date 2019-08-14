#pragma once

#include <string>
#include <vector>
#include <tuple>

// return the maximum of three values or zero
inline std::tuple<int, int> _max(int left, int up, int diag);

inline int _score_alignment(char alpha, char beta, int match, int mismatch, int gap);

using Matrix = std::vector<std::vector<int>>;
void _print_matrix(Matrix m);

int smith_waterman(std::string seq1, std::string seq2, int match, int mismatch, int gap, bool just_score);

void test_smith_waterman();