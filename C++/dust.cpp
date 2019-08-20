#include <algorithm>	// std::count
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
	// reserve twice needed capacity for hash table to minimize collisions
	record.reserve(triplets.size() * 2);

	for (auto triplet : triplets) {
		// triplet not recorded yet
		if (record.find(triplet) == record.end()) {
			// count occurrances
			occurrance = std::count(triplets.begin(), triplets.end(), triplet);
			record[triplet] = occurrance * (occurrance - 1) / 2.0;
		}
	}
	// sum the scores
	for (auto iter = record.begin(); iter != record.end(); ++iter) {
		total_score += iter->second;
	}
	return total_score / ((double)word.length() / (double)pattern_len);
}

Blastn::IndexedSequenceMap dust_filter(Blastn::IndexedSequenceMap data, double threshold, int word_len, int triplet_len)
{
	Blastn::IndexedSequenceMap filtered_result;
	threshold = threshold * (word_len - triplet_len - 1) / 2;

	// breaks words into subsequences of triplets
	for (auto name_seqmap = data.begin(); name_seqmap != data.end(); ++name_seqmap) {
		for (auto word_indices = name_seqmap->second.begin(); word_indices != name_seqmap->second.end(); ++word_indices) {
			// words that score above the threshold will not be added to the filtered result
			if (_dust(word_indices->first, triplet_len) < threshold) {
				filtered_result[name_seqmap->first] = Blastn::IndexedWordMap {
					std::pair<std::string, std::vector<int>>{ word_indices->first, word_indices->second }
				};
			}
		}
	}
	return filtered_result;
}

void test_dust()
{
	std::string words[3] = {
		"AACAACAACAAA",
		"AAAAAAAAAAAA",
		"AGCTCGATGTAG",
	};

	for (auto word : words)
		std::cout << _dust(word, 3) << std::endl;
}
