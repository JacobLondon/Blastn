#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Blastn {

// type redefinitions

using s32 = int32_t;
using u32 = uint32_t;
using f32 = float;

using string = std::string;

template<typename T, typename U>
using dict = std::unordered_map<T, U>;

template<typename T>
using vector = std::vector<T>;

// convenient globals

const string SGap = "-";
const char CGap = '-';
const string Invalid = "\0";

enum SW {
    NO_PRESERVE_MEM,
    PRESERVE_MEM,
    MULTI_THREAD,
    FPGA,
};

/**
 * @brief The details for what a match has, a word, subject indices, query indices.
 */
struct Match {
    Match(string word, vector<u32> subject_indices, vector<u32> query_indices);
    string word;
    vector<u32> subject_indices;
    vector<u32> query_indices;
};

struct AdjacentPair {
    AdjacentPair(string word1, string word2, u32 sindex1, u32 qindex1, u32 sindex2, u32 qindex2);
    string word1, word2;
    u32 length;
    u32 sindex1, sindex2;
    u32 qindex1, qindex2;
};

struct Extended {
    Extended(string extended_pair, u32 sindex, u32 qindex, s32 score);
    string extended_pair;
    u32 sindex;
    u32 qindex;
    s32 score;
};

struct HSP {
    HSP(string subject_id, string query_id, string extended_pair, u32 sindex, u32 qindex, s32 sw_score);

    // calculated in constructor
    string subject_id;
    string query_id;
    string extended_pair;
    u32 subject_start, subject_end;
    u32 query_start, query_end;
    s32 sw_score;

    // calculate later

    f32 percentage_id = 0;
    u32 matches = 0;
    u32 mismatches = 0;
    u32 gaps = 0;

    double evalue = 0;
    double bitscore = 0;
};

/**
 * @brief Used in Smith Waterman for the matrices
 */
using Matrix = vector<vector<u32>>;
string str(Matrix m);
/**
 * @brief Map sequence names to their sequence.
 */
using SequenceMap = dict<string, string>;
string str(SequenceMap s);

/**
 * @brief Intermediate, map a word to its indices.
 */
using IndexedWordMap = dict<string, vector<u32>>;
/**
 * @brief Map sequence names to all words mapped to a vector or indices where each word appears in its sequence.
 */
using IndexedSequenceMap = dict<string, IndexedWordMap>;
string str(IndexedSequenceMap s);

/**
 * @brief Intermediate, map a query name to its Match objects
 */
using MatchedMatchesMap = dict<string, vector<Match>>;
/**
 * @brief Subject name mapped to a query name mapped to a vector of Match objects
 */
using MatchedSequenceMap = dict<string, MatchedMatchesMap>;
string str(MatchedSequenceMap s);

/**
 * @brief Intermediate, map a query name to its AdjacentPair objects
 */
using PairedMatchesMap = dict<string, vector<AdjacentPair>>;
/**
 * @brief Subject name mapped to a query name mapped to a vector of AdjacentPair objects 
 */
using PairedSequenceMap = dict<string, PairedMatchesMap>;
string str(PairedSequenceMap s);

/**
 * @brief Intermediate, map a query name to its Extended pair objects
 */
using ExtendedPairsMap = dict<string, vector<Extended>>;
/**
 * @brief Subject name mapped to a query name mapped to a vector of Extended pair objects
 */
using ExtendedSequenceMap = dict<string, ExtendedPairsMap>;
string str(ExtendedSequenceMap s);

/**
 * @brief Output data structure
 */
string str(vector<HSP> s);

} // Blastn