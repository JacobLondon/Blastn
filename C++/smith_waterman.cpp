#include <algorithm>
#include "smith_waterman.hpp"

enum Direction {
	_INVALID,
	LEFT,
	UP,
	DIAG
};

const std::string sGAP = "-";
const char cGAP = '-';

// return the maximum of three values or zero
inline IValueTuple _max(int32_t left, int32_t up, int32_t diag) {
	IValueTuple max = { 0, 0 };

	if (left > 0) {
		max.value = left;
		max.index = LEFT;
	}
	if (up > max.value) {
		max.value = up;
		max.index = UP;
	}
	if (diag > max.value) {
		max.value = diag;
		max.index = DIAG;
	}

	return max;
}

inline int32_t _score_alignment(char alpha, char beta, int32_t match, int32_t mismatch, int32_t gap) {
	if (alpha == beta)
		return match;
	else if (cGAP == alpha || cGAP == beta)
		return gap;
	else
		return mismatch;
}

int32_t smith_waterman(std::string seq1,
				   std::string seq2,
				   int32_t match,
				   int32_t mismatch,
				   int32_t gap,
				   bool just_score) {

	int32_t rows = seq1.length();
	int32_t cols = seq2.length();
	int32_t i = 0;
	int32_t j = 0;

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
	int32_t max_score = 0;
	int32_t max_i = 1;
	int32_t max_j = 1;
	int32_t left, up, diag;
	IValueTuple greatest;

	// fill score matrix
	for (i = 1; i <= cols; i++) {
		for (j = 1; j <= rows; j++) {

			// determine possible scores of the current cell
			left = score_matrix[i - 1][j] + gap;
			up = score_matrix[i][j - 1] + gap;
			diag = score_matrix[i - 1][j - 1] + _score_alignment(seq1[i - 1], seq2[j - 1], match, mismatch, gap);

			// find greatest: load direction into point_matrix, score into score_matrix
			greatest = _max(left, up, diag);
			point_matrix[i][j] = greatest.index;
			score_matrix[i][j] = greatest.value;

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
			temp1 = sGAP;
			temp2 = seq2[--j];
		}
		// left movement
		else if (point_matrix[i][j] == LEFT) {
			temp1 = seq1[--i];
			temp2 = sGAP;
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
	float64_t similarity_percent = 0.0;

	for (int32_t x = 0; x < rows; x++) {
		std::string a1{ aligned1[x] };
		std::string a2{ aligned2[x] };

		// char in both, append to output
		if (a1 == a2) {
			output_alignment.append(a1);
			similarity_percent += 1.0;
		}
		// no match, gap append to output string
		else if (a1 != a2 && a1 != sGAP && a2 != sGAP) {
			output_alignment.append(sGAP);
		}
		// gap in both
		else if (a1 == sGAP || a2 == sGAP) {
			output_alignment.append(sGAP);
		}
	}

	// similarity number to percent
	similarity_percent = similarity_percent / (float64_t)aligned1.length() * 100.0;

	std::cout << "\nScore matrix:" << std::endl;
	Blastn::print(score_matrix);
	std::cout << "\nPoint matrix" << std::endl;
	Blastn::print(point_matrix);

	std::cout << "Sequence A:\n" << seq1 << std::endl;
	std::cout << "Sequence B:\n" << seq2 << std::endl;

	std::cout << "\nSimilarity: " << similarity_percent << std::endl;
	std::cout << "Max Score: " << max_score << std::endl;

	std::cout << "\nAligned A: " << aligned1 << std::endl;
	std::cout << "Aligned B: " << aligned2 << std::endl;
	std::cout << "   Output: " << output_alignment << std::endl;

	return max_score;
}

Blastn::IndexedSequenceMap smith_waterman_filter(Blastn::IndexedSequenceMap data, int32_t minscore, int32_t match, int32_t mismatch, int32_t gap)
{
	// traverse each sequence
	for (auto name_seqmap = data.begin(); name_seqmap != data.end(); ++name_seqmap) {
		// get the word from each element in each sequence
		for (auto word_indices = name_seqmap->second.begin(); word_indices != name_seqmap->second.end(); ++word_indices) {
			if (smith_waterman(word_indices->first, word_indices->first, match, mismatch, gap, true) < minscore)
				data[name_seqmap->first].erase(word_indices);
		}
	}
	return data;
}
