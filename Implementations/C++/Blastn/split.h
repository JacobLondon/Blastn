#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

std::vector<std::string> split(std::string input, int length) {
	std::vector<std::string> words;
	int numWords = input.length() - length + 1;

	// get all substrings of the same length in the input
	for (int i = 0; i < numWords; i++) {
		words.push_back(input.substr(i, length));
	}

	return words;
}

void testSplit() {
	std::string input = "ATCGAC";
	int length = 3;

	std::vector<std::string> words = split(input, length);

	std::vector<std::string> result = {
		"ATC",
		"TCG",
		"CGA",
		"GAC"
	};

	assert(words == result);

	std::cout << "split.h test passed." << std::endl;
}