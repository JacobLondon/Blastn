#pragma once
#include "types.hpp"

// globals vars
namespace Blastn {
	extern char Seperator = '>';
	extern int32_t SplitLength = 11;

	extern int32_t SwMinscore = 6;
	extern int32_t SwMatch = 2;
	extern int32_t SwMismatch = -1;
	extern int32_t SwGap = -1;

	extern float32_t DustThreshold = 2;
	extern int32_t DustPatternLength = 3;
}