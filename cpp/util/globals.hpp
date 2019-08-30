#pragma once
#include "types.hpp"

/**
 * Global variables
 */

namespace Blastn {
	char Seperator = '>';			// .fa and .fasta line seperator
	int32_t SplitLength = 11;		// word length

	int32_t SwMinscore = 6;			// min smith waterman score before filtering out
	int32_t SwMatch = 2;			// smith waterman match score
	int32_t SwMismatch = -1;		// smith waterman mismatch score
	int32_t SwGap = -1;				// smith waterman gap score

	float32_t DustThreshold = 2;	// dust threshold score before filtering out
	int32_t DustPatternLength = 3;	// length of patterns for dust to look for
}
