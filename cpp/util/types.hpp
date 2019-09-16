#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// what is expected
using s32 = signed int;
using u32 = unsigned int;
using f32 = float;
using f64 = double;

using string = std::string;

template<typename T, typename U>
using dict = std::unordered_map<T, U>;

template<typename T>
using vector = std::vector<T>;

/**
 * @brief The details for what a match has, a word, data indices, query indices.
 */
class Match {
public:
	Match(string word, vector<u32> data_indices, vector<u32> query_indices);
	string word;
	vector<u32> data_indices;
	vector<u32> query_indices;
};

class AdjacentPair {
public:
	AdjacentPair(string word1, string word2, u32 dindex1, u32 qindex1, u32 dindex2, u32 qindex2);
	string word1, word2;
	u32 length;
	u32 dindex1, dindex2;
	u32 qindex1, qindex2;
};

class Extended {
public:
	Extended(string extended_pair, s32 dindex);
	string extended_pair;
	s32 dindex;
};

class Sorted {
public:
	Sorted(string extended_pair, s32 dindex, s32 score);
	string extended_pair;
	s32 dindex;
	s32 score;
};

namespace Blastn {
	const string SGap = "-";
	const char CGap = '-';
	const string Invalid = "\0";
	/**
	 * @brief Used in Smith Waterman for the matrices
	 */
	using Matrix = vector<vector<u32>>;
	void print(Matrix m);
	/**
	 * @brief Map sequence names to their sequence.
	 */
	using SequenceMap = dict<string, string>;
	void print(SequenceMap s);

	/**
	 * @brief Intermediate, map a word to its indices.
	 */
	using IndexedWordMap = dict<string, vector<u32>>;
	/**
	 * @brief Map sequence names to all words mapped to a vector or indices where each word appears in its sequence.
	 */
	using IndexedSequenceMap = dict<string, IndexedWordMap>;
	void print(IndexedSequenceMap s);

	/**
	 * @brief Intermediate, map a query name to its Match objects
	 */
	using MatchedMatchesMap = dict<string, vector<Match>>;
	/**
	 * @brief Data name mapped to a query name mapped to a vector of Match objects
	 */
	using MatchedSequenceMap = dict<string, MatchedMatchesMap>;
	void print(MatchedSequenceMap);

	/**
	 * @brief Intermediate, map a query name to its AdjacentPair objects
	 */
	using PairedMatchesMap = dict<string, vector<AdjacentPair>>;
	/**
	 * @brief Data name mapped to a query name mapped to a vector of AdjacentPair objects 
	 */
	using PairedSequenceMap = dict<string, PairedMatchesMap>;

	/**
	 * @brief Intermediate, map a query name to its Extended pair objects
	 */
	using ExtendedPairsMap = dict<string, vector<Extended>>;
	/**
	 * @brief Data name mapped to a query name mapped to a vector of Extended pair objects
	 */
	using ExtendedSequenceMap = dict<string, ExtendedPairsMap>;

	/**
	 * @brief Intermediate, map a query to its Sorted/Extended object
	 */
	using SortedPairsMap = dict<string, vector<Sorted>>;
	/**
	 * @brief Data name mapped to a query name mapped to a vector of Sorted objects
	 */
	using SortedSequenceMap = dict<string, SortedPairsMap>;

}
