#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

enum choice {
	SCORE,
	ALIGNMENT
};

enum {
	DIAG,
	UP,
	LEFT
};

const std::string GAP_CHAR = "-";

// return the maximum of three values or zero
std::tuple<int, int> max3(int val1, int val2, int val3) {
	int max = 0;
	int index = 0;

	if (val1 > 0) {
		max = val1;
		index = 1;
	}
	if (val2 > max) {
		max = val2;
		index = 2;
	}
	if (val3 > max) {
		max = val3;
		index = 3;
	}

	std::tuple<int, int> result = { index, max };
	return result;
}

int cmp(char alpha, char beta, int match, int mismatch, int gap) {
	if (alpha == beta)
		return match;
	else if ('-' == alpha || '-' == beta)
		return gap;
	else
		return mismatch;
}

typedef std::vector<std::vector<int>> Matrix;
void printMat(Matrix m) {
	for (auto v : m) {
		for (auto score : v) {
			std::cout << score << ". ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}
float smithWaterman(std::string seqA, std::string seqB, int match, int mismatch, int gap, int choice) {

	int xLen = seqA.length();
	int yLen = seqB.length();

	float maxScore = 0;
	int maxI = 1, maxJ = 1;

	// initialize empty matrices
	Matrix scoreMatrix, pointMatrix;

	// initialize matrices with zeros
	for (int i = 0; i <= yLen; i++) {
		std::vector<int> temp;
		for (int j = 0; j <= xLen; j++) {
			temp.push_back(0);
		}
		scoreMatrix.push_back(temp);
		pointMatrix.push_back(temp);
	}

	// to fill the matrices
	int i = 0, j = 0;
	int left, up, diag;
	std::tuple<int, int> greatest;

	// fill score matrix
	for (i = 1; i <= yLen; i++) {
		for (j = 1; j <= xLen; j++) {

			// determine possible scores of the current cell
			left = scoreMatrix[i - 1][j] + gap;
			up = scoreMatrix[i][j - 1] + gap;
			diag = scoreMatrix[i - 1][j - 1] + cmp(seqA[i - 1], seqB[j - 1], match, mismatch, gap);

			// find greatest: load direction into pointMatrix, score into scoreMatrix
			greatest = max3(left, up, diag);
			pointMatrix[i][j] = std::get<0>(greatest);
			scoreMatrix[i][j] = std::get<1>(greatest);

			// record high score
			if (scoreMatrix[i][j] >= maxScore) {
				maxI = i;
				maxJ = j;
				maxScore = scoreMatrix[i][j];
			}
		}
	}

	std::string tempA, tempB;
	std::string alignedA = "";
	std::string alignedB = "";
	i = maxI;
	j = maxJ;

	while (pointMatrix[i][j] != 0) {
		// diagnal movement
		if (pointMatrix[i][j] == 3) {
			tempA = seqA[i - 1];
			tempB = seqB[j - 1];
			i--; j--;
		}
		else if (pointMatrix[i][j] == 2) {
			tempA = GAP_CHAR;
			tempB = seqB[j - 1];
			j--;
		}
		else if (pointMatrix[i][j] == 1) {
			tempA = seqA[i - 1];
			tempB = GAP_CHAR;
			i--;
		}

		// append the chars to the aligned build string
		alignedA.append(tempA);
		alignedB.append(tempB);
	}

	// reverse the strings to forward order
	std::reverse(alignedA.begin(), alignedA.end());
	std::reverse(alignedB.begin(), alignedB.end());

	// accumulator strings for the output
	std::string outputAlignment = "";
	float similarityPercent = 0.0;

	for (int x = 0; x < xLen; x++) {
		std::string a1{ alignedA[x] };
		std::string a2{ alignedB[x] };

		// char in both, append to output
		if (a1 == a2) {
			outputAlignment.append(a1);
			similarityPercent += 1.0;
		}
		// no match, gap append to output string
		else if (a1 != a2 && a1 != GAP_CHAR && a2 != GAP_CHAR) {
			outputAlignment.append(GAP_CHAR);
		}
		// gap in both
		else if (a1 == GAP_CHAR || a2 == GAP_CHAR) {
			outputAlignment.append(GAP_CHAR);
		}
	}

	// similarity number to percent
	similarityPercent = similarityPercent / (float)alignedA.length() * 100.0;

	std::cout << "\nScore matrix:" << std::endl;
	printMat(scoreMatrix);
	std::cout << "\nPoint matrix" << std::endl;
	printMat(pointMatrix);
	
	std::cout << "Sequence A:\n" << seqA << std::endl;
	std::cout << "Sequence B:\n" << seqB << std::endl;

	std::cout << "\nSimilarity: " << similarityPercent << std::endl;
	std::cout << "Max Score: " << maxScore << std::endl;

	std::cout << "\nAligned A: " << alignedA << std::endl;
	std::cout << "Aligned B: " << alignedB << std::endl;
	std::cout << "   Output: " << outputAlignment << std::endl;

	return maxScore;
}

void testSmithWaterman() {
	std::string seqA = "ATCGAC";
	std::string seqB = "ACCGAC";

	int match	 = 2;
	int mismatch = -1;
	int gap      = -1;

	int choice = SCORE;

	float result = smithWaterman(seqA, seqB, match, mismatch, gap, choice);

	//std::cout << "Score: " << result << std::endl;
}