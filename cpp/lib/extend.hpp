#pragma once
#include "../util/types.hpp"

/**
 * @brief Extend a pair of words where each word is in the same database and query. In addition,
 *        the distance between the words in the database is less than the length of the query.
 *        This algorithm will extend the left word to the left and perform the Smith Waterman
 *        algorithm on it vs the database equivlanent. Then the left word will be extended right
 *        until it either reaches the right word, or gaps need to be added. After, the right word
 *        is extended right and scored.
 * @param pair The AdjacentPair with all of the information to know where each word is in their respective datastructures.
 * @param query The current query dataset to extend the pair from.
 * @param data The current data dataset to extend the pair to.
 * @param match The smith waterman score for a match.
 * @param mismatch The smith waterman score for a mismatch.
 * @param gap The smith waterman score for a gap.
 * @param minscore The minimum smith waterman score from the extended values. Pairs with scores below this are removed.
 * @param score Indicate to score and remove words on true.
 * @param printing Indicate to print the values at the end of the function.
 * @return The extended, aligned match.
 */
Extended extend_and_score(AdjacentPair pair,
						  string query,
						  string data,
						  s32 match,
						  s32 mismatch,
						  s32 gap,
						  s32 minscore,
						  bool score,
						  bool printing);

/*
 * @brief: Given adjacent pairs, the database and query, extend the pairs from the query to the database.
 * @param pairs:    The mapped data of adjacent pairs to extend and filter while extending.
 * @param query : The map of query names to their entire query sequence.
 * @param data : The map of data names to their entire data sequence.
 * @param minscore : The minimum smith waterman score allowed before needing to remove the word.
 * @param match : The smith waterman score when two characters are the same.
 * @param mismatch : The smith waterman score when two characters are not the same.
 * @param gap : The smith waterman score when there is a gap character.
 * @return A map of data names to query names to a list of extended matches with their data base index.
 */
Blastn::ExtendedSequenceMap extend_filter(Blastn::PairedMatchesMap& pairs,
										  Blastn::SequenceMap& query,
										  Blastn::SequenceMap& data,
										  s32 minscore,
										  s32 match,
										  s32 mismatch,
										  s32 gap);
