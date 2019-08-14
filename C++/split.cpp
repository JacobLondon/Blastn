#include "split.hpp"

std::vector<std::string> split_to_words(std::string input, int word_len) {
	int num_words = input.length() - word_len + 1;
	std::vector<std::string> words;
	words.reserve(num_words);

	// get all substrings of the same length in the input
	for (int i = 0; i < num_words; i++) {
		words.push_back(input.substr(i, word_len));
	}

	return words;
}

void test_split_to_words() {
	std::string input = "ATCGAC";
	int length = 3;

	std::vector<std::string> words = split_to_words(input, length);

	std::vector<std::string> result = {
		"ATC",
		"TCG",
		"CGA",
		"GAC"
	};

	assert(words == result);

	std::cout << "split.h test passed." << std::endl;
}