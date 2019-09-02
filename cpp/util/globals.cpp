#include "globals.hpp"

namespace Blastn {
	char Seperator = '>';			// .fa and .fasta line seperator
	int32_t SplitLength = 4;		// word length

	int32_t SwMinscore = 0;			// min smith waterman score before filtering out
	int32_t SwMatch = 2;			// smith waterman match score
	int32_t SwMismatch = -1;		// smith waterman mismatch score
	int32_t SwGap = -1;				// smith waterman gap score

	float32_t DustThreshold = 0.2;	// dust threshold score before filtering out
	int32_t DustPatternLength = 3;	// length of patterns for dust to look for

	std::string Output = "blastn_out.txt";
}
