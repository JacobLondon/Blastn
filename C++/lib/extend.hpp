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
std::string extend_and_score(AdjacentPair pair,
							 std::string query,
							 std::string data,
							 int32_t match,
							 int32_t mismatch,
							 int32_t gap,
							 int32_t minscore,
							 bool score,
							 bool printing);
