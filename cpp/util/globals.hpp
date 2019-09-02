#pragma once
#include "types.hpp"

/**
 * Global variables
 */

namespace Blastn {
	extern char Seperator;				// .fa and .fasta line seperator
	extern int32_t SplitLength;			// word length

	extern int32_t SwMinscore;			// min smith waterman score before filtering out
	extern int32_t SwMatch;				// smith waterman match score
	extern int32_t SwMismatch;			// smith waterman mismatch score
	extern int32_t SwGap;				// smith waterman gap score

	extern float32_t DustThreshold;		// dust threshold score before filtering out
	extern int32_t DustPatternLength;	// length of patterns for dust to look for

	extern std::string Output;
}
