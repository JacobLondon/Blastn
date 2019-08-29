#include "split.hpp"

std::vector<std::string> split_to_words(std::string input, int32_t word_len) {
	int32_t num_words = input.length() - word_len + 1;
	std::vector<std::string> words;
	words.reserve(num_words);

	// get all substrings of the same length in the input
	for (int32_t i = 0; i < num_words; i++) {
		words.push_back(input.substr(i, word_len));
	}

	return words;
}
