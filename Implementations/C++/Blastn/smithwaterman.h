#pragma once

#include <string>
#include <vector>

const int MATCH = 2;
const int MISMATCH = -1;
const int GAP = -1;

enum {
	DIAG,
	UP,
	LEFT
};

//int max(int val1, int val2, int val3);
float smithWaterman(std::string, std::string);

// return the maximum of three values or zero
int max3(int val1, int val2, int val3) {
	int max = 0;

	if (val1 > 0)
		max = val1;
	if (val2 > max)
		max = val2;
	if (val3 > max)
		max = val3;

	return max;
}

float smithWaterman(std::string seqA, std::string seqB) {
	
	int xLen = seqA.length();
	int yLen = seqB.length();

	int maxScore = 0;
	int max_i = 1, max_j = 1;

	// initialize empty matrices
	typedef std::vector<std::vector<int>> Matrix;
	Matrix scoreMatrix, pointMatrix;

	// fill with zeros
	for (int i = 0; i < yLen; i++) {
		for (int j = 0; j < xLen; j++) {
			scoreMatrix.push_back(0);
		}
	}

	

}
