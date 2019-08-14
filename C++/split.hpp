#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

std::vector<std::string> split_to_words(std::string input, int word_len);

void test_split_to_words();