#include <algorithm>
#include "smith_waterman.hpp"

enum Direction {
	_INVALID,
	LEFT,
	UP,
	DIAG
};

// return the maximum of three values or zero
inline IValueTuple max(s32 left, s32 up, s32 diag)
{
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

inline s32 score_alignment(char alpha, char beta, s32 match, s32 mismatch, s32 gap)
{
	if (alpha == beta)
		return match;
	else if (Blastn::CGap == alpha || Blastn::CGap == beta)
		return gap;
	else
		return mismatch;
}

s32 smith_waterman(string seq1,
				   string seq2,
				   s32 match,
				   s32 mismatch,
				   s32 gap,
				   bool just_score)
{

	u32 rows = (u32)seq1.length();
	u32 cols = (u32)seq2.length();
	u32 i = 0;
	u32 j = 0;

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
	s32 max_score = 0;
	u32 max_i = 1;
	u32 max_j = 1;
	s32 left, up, diag;
	IValueTuple greatest;

	// fill score matrix
	for (i = 1; i <= cols; i++) {
		for (j = 1; j <= rows; j++) {

			// determine possible scores of the current cell
			left = score_matrix[i - 1][j] + gap;
			up = score_matrix[i][j - 1] + gap;
			diag = score_matrix[i - 1][j - 1] + score_alignment(seq1[i - 1], seq2[j - 1], match, mismatch, gap);

			// find greatest: load direction into point_matrix, score into score_matrix
			greatest = max(left, up, diag);
			point_matrix[i][j] = greatest.index;
			score_matrix[i][j] = greatest.value;

			// record high score
			if ((s32)score_matrix[i][j] >= (s32)max_score) {
				max_i = i;
				max_j = j;
				max_score = score_matrix[i][j];
			}
		}
	}

	if (just_score)
		return max_score;

	string temp1, temp2;
	string aligned1 = "";
	string aligned2 = "";
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
			temp1 = Blastn::SGap;
			temp2 = seq2[--j];
		}
		// left movement
		else if (point_matrix[i][j] == LEFT) {
			temp1 = seq1[--i];
			temp2 = Blastn::SGap;
		}

		// append the chars to the aligned build string
		aligned1.append(temp1);
		aligned2.append(temp2);
	}

	// reverse the strings to forward order
	std::reverse(aligned1.begin(), aligned1.end());
	std::reverse(aligned2.begin(), aligned2.end());

	// accumulator strings for the output
	string output_alignment = "";
	f64 similarity_percent = 0.0;

	for (u32 x = 0; x < rows; x++) {
		string a1{ aligned1[x] };
		string a2{ aligned2[x] };

		// char in both, append to output
		if (a1 == a2) {
			output_alignment.append(a1);
			similarity_percent += 1.0;
		}
		// no match, gap append to output string
		else if (a1 != a2 && a1 != Blastn::SGap && a2 != Blastn::SGap) {
			output_alignment.append(Blastn::SGap);
		}
		// gap in both
		else if (a1 == Blastn::SGap || a2 == Blastn::SGap) {
			output_alignment.append(Blastn::SGap);
		}
	}

	// similarity number to percent
	similarity_percent = similarity_percent / (f64)aligned1.length() * 100.0;

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

Blastn::IndexedSequenceMap smith_waterman_filter(Blastn::IndexedSequenceMap& data, s32 minscore, s32 match, s32 mismatch, s32 gap)
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
