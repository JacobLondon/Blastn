#include <iostream>
#include <unordered_map>
#include <vector>

#include "dust.hpp"
#include "split.hpp"

double _dust(std::string word, int pattern_len)
{
	double total_score = 0;
	int occurrance;
	std::vector<std::string> triplets = split_to_words(word, pattern_len);
	std::unordered_map<std::string, double> record;

	for (int i = 0; i < triplets.size(); i++) {
		// triplet not recorded yet
		if (record.find(triplets[i]) == record.end()) {
			// count occurrances
			occurrance = 0;
			for (std::string triplet : triplets) {
				if (triplets[i] == triplet)
					occurrance++;
			}
			record.insert(std::pair<std::string, double> { triplets[i], occurrance * (occurrance - 1) / 2.0 });
		}
	}
	// sum the scores
	for (auto iter = record.begin(); iter != record.end(); ++iter) {
		total_score += iter->second / (word.length() / pattern_len);
	}
	return total_score;
}

void test_dust()
{
	std::string word = "AGCTCGATGTAG";
	double score = _dust(word, word.length());
	std::cout << score << std::endl;
}
