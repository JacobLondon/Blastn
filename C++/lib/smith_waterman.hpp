#pragma once
#include "../util/types.hpp"

// smith waterman
struct IValueTuple {
	int32_t index;
	int32_t value;
};

// return the maximum of three values or zero
inline IValueTuple _max(int32_t left, int32_t up, int32_t diag);

inline int32_t _score_alignment(char alpha, char beta, int32_t match, int32_t mismatch, int32_t gap);

int32_t smith_waterman(std::string seq1, std::string seq2, int32_t match, int32_t mismatch, int32_t gap, bool just_score);
Blastn::IndexedSequenceMap smith_waterman_filter(Blastn::IndexedSequenceMap data, int32_t minscore, int32_t match, int32_t mismatch, int32_t gap);
