#include "globals.hpp"

namespace Blastn {
	char Seperator = '>';		// .fa and .fasta line seperator
	u32 SplitLength = 4;		// word length

	s32 SwMinscore = 0;			// min smith waterman score before filtering out
	s32 SwMatch = 2;			// smith waterman match score
	s32 SwMismatch = -1;		// smith waterman mismatch score
	s32 SwGap = -1;				// smith waterman gap score

	f64 DustThreshold = 0.2f;	// dust threshold score before filtering out
	u32 DustPatternLength = 3;	// length of patterns for dust to look for

	string Output = "blastn_out.txt";
}
