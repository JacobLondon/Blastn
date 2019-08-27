#pragma once

#include <string>
#include <unordered_map>
#include <vector>

/**
 * \brief The details for what a match has, a word, data indices, query indices.
 */
class Match {
public:
	Match(std::string word, std::vector<int> data_indices, std::vector<int> query_indices);
	std::string word;
	std::vector<int> data_indices;
	std::vector<int> query_indices;
};

class AdjacentPair {
public:
	AdjacentPair(std::string word1, std::string word2, int dindex1, int qindex1, int dindex2, int qindex2);
	std::string word1, word2;
	int length;
	int dindex1, dindex2;
	int qindex1, qindex2;
};

namespace Blastn {
	/**
	 * \brief Used in Smith Waterman for the matrices
	 */
	using Matrix = std::vector<std::vector<int>>;
	/**
	 * \brief Map sequence names to their sequence.
	 */
	using SequenceMap = std::unordered_map<std::string, std::string>;
	/**
	 * \brief Intermediate, map a word to its indices.
	 */
	using IndexedWordMap = std::unordered_map<std::string, std::vector<int>>;
	/**
	 * \brief Map sequence names to all words mapped to a vector or indices where each word appears in its sequence.
	 */
	using IndexedSequenceMap = std::unordered_map<std::string, IndexedWordMap>;
	/**
	 * \brief Intermediate, map a word to its Match objects
	 */
	using MatchedMatchesMap = std::unordered_map<std::string, std::vector<Match>>;
	/**
	 * \brief Data name mapped to a query name mapped to a vector of Match objects
	 */
	using MatchedSequenceMap = std::unordered_map<std::string, MatchedMatchesMap>;

}

