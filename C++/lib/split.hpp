#pragma once
#include "../util/types.hpp"

/**
 * @brief Split an input string into words of a given length.
 */
std::vector<std::string> split_to_words(std::string input, int32_t word_len);
