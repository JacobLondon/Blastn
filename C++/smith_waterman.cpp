#include <algorithm>
#include <iostream>
#include "smith_waterman.hpp"

enum Direction {
	_INVALID,
	LEFT,
	UP,
	DIAG
};

const std::string GAP_CHAR = "-";

// return the maximum of three values or zero
inline std::tuple<int, int> _max(int left, int up, int diag) {
	int greatest = 0;
	int index = 0;

	if (left > 0) {
		greatest = left;
		index = LEFT;
	}
	if (up > greatest) {
		greatest = up;
		index = UP;
	}
	if (diag > greatest) {
		greatest = diag;
		index = DIAG;
	}

	std::tuple<int, int> result = { index, greatest };
	return result;
}

inline int _score_alignment(char alpha, char beta, int match, int mismatch, int gap) {
	if (alpha == beta)
		return match;
	else if ('-' == alpha || '-' == beta)
		return gap;
	else
		return mismatch;
}

int smith_waterman(std::string seq1,
				   std::string seq2,
				   int match,
				   int mismatch,
				   int gap,
				   bool just_score) {

	int rows = seq1.length();
	int cols = seq2.length();
	int i = 0;
	int j = 0;

	// initialize empty matrices
	Blastn::Matrix score_matrix, point_matrix;
	score_matrix.reserve(cols);
	point_matrix.reserve(cols);

	// initialize matrices vectors of length rows + 1 with zeros
	for (i = 0; i <= cols; i++) {
		// emblace_back's vector initializer with (length, value to fill)
		score_matrix.emplace_back(rows + 1, 0);
		point_matrix.emplace_back(rows + 1, 0);
	}

	// to fill the matrices
	int max_score = 0;
	int max_i = 1;
	int max_j = 1;
	int left, up, diag;
	std::tuple<int, int> greatest;

	// fill score matrix
	for (i = 1; i <= cols; i++) {
		for (j = 1; j <= rows; j++) {

			// determine possible scores of the current cell
			left = score_matrix[i - 1][j] + gap;
			up = score_matrix[i][j - 1] + gap;
			diag = score_matrix[i - 1][j - 1] + _score_alignment(seq1[i - 1], seq2[j - 1], match, mismatch, gap);

			// find greatest: load direction into point_matrix, score into score_matrix
			greatest = _max(left, up, diag);
			point_matrix[i][j] = std::get<0>(greatest);
			score_matrix[i][j] = std::get<1>(greatest);

			// record high score
			if (score_matrix[i][j] >= max_score) {
				max_i = i;
				max_j = j;
				max_score = score_matrix[i][j];
			}
		}
	}

	if (just_score)
		return max_score;

	std::string temp1, temp2;
	std::string aligned1 = "";
	std::string aligned2 = "";
	i = max_i;
	j = max_j;

	while (point_matrix[i][j] != 0) {
		// diagnal movement
		if (point_matrix[i][j] == DIAG) {
			temp1 = seq1[--i];
			temp2 = seq2[--j];
		}
		// upwards movement
		else if (point_matrix[i][j] == UP) {
			temp1 = GAP_CHAR;
			temp2 = seq2[--j];
		}
		// left movement
		else if (point_matrix[i][j] == LEFT) {
			temp1 = seq1[--i];
			temp2 = GAP_CHAR;
		}

		// append the chars to the aligned build string
		aligned1.append(temp1);
		aligned2.append(temp2);
	}

	// reverse the strings to forward order
	std::reverse(aligned1.begin(), aligned1.end());
	std::reverse(aligned2.begin(), aligned2.end());

	// accumulator strings for the output
	std::string output_alignment = "";
	double similarity_percent = 0.0;

	for (int x = 0; x < rows; x++) {
		std::string a1{ aligned1[x] };
		std::string a2{ aligned2[x] };

		// char in both, append to output
		if (a1 == a2) {
			output_alignment.append(a1);
			similarity_percent += 1.0;
		}
		// no match, gap append to output string
		else if (a1 != a2 && a1 != GAP_CHAR && a2 != GAP_CHAR) {
			output_alignment.append(GAP_CHAR);
		}
		// gap in both
		else if (a1 == GAP_CHAR || a2 == GAP_CHAR) {
			output_alignment.append(GAP_CHAR);
		}
	}

	// similarity number to percent
	similarity_percent = similarity_percent / (double)aligned1.length() * 100.0;

	std::cout << "\nScore matrix:" << std::endl;
	print(score_matrix);
	std::cout << "\nPoint matrix" << std::endl;
	print(point_matrix);

	std::cout << "Sequence A:\n" << seq1 << std::endl;
	std::cout << "Sequence B:\n" << seq2 << std::endl;

	std::cout << "\nSimilarity: " << similarity_percent << std::endl;
	std::cout << "Max Score: " << max_score << std::endl;

	std::cout << "\nAligned A: " << aligned1 << std::endl;
	std::cout << "Aligned B: " << aligned2 << std::endl;
	std::cout << "   Output: " << output_alignment << std::endl;

	return max_score;
}

void print(Blastn::Matrix m) {
	for (auto v : m) {
		for (auto score : v) {
			std::cout << score << ". ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void test_smith_waterman() {
	std::string seq1 = "ATCGAC";
	std::string seq2 = "ACCGAC";

	int match = 2;
	int mismatch = -1;
	int gap = -1;

	int result = smith_waterman(seq1, seq2, match, mismatch, gap, false);
}