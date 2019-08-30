#include "dust.hpp"
#include "split.hpp"	// split_to_words
#include <algorithm>	// count

float64_t dust(std::string word, int32_t pattern_len)
{
	float64_t total_score = 0;
	int32_t occurrance;
	std::vector<std::string> triplets = split_to_words(word, pattern_len);
	std::unordered_map<std::string, int32_t> record;
	// reserve double necessary capacity for hash table to minimize collisions
	record.reserve(triplets.size() * 2);

	for (auto triplet : triplets) {
		// triplet not recorded yet
		if (record.find(triplet) == record.end()) {
			// count occurrances
			occurrance = std::count(triplets.begin(), triplets.end(), triplet);
			record[triplet] = occurrance * (occurrance - 1) / 2;
		}
	}
	// sum the scores
	for (auto iter = record.begin(); iter != record.end(); ++iter)
		total_score += iter->second;
	return total_score / (word.length() - pattern_len);
}

Blastn::IndexedSequenceMap dust_filter(Blastn::IndexedSequenceMap data, float64_t threshold, int32_t word_len, int32_t pattern_len)
{
	Blastn::IndexedSequenceMap filtered_result;
	threshold = threshold * (word_len - pattern_len - 1) / 2;

	// breaks words into subsequences of triplets
	for (auto name_seqmap = data.begin(); name_seqmap != data.end(); ++name_seqmap) {
		for (auto word_indices = name_seqmap->second.begin(); word_indices != name_seqmap->second.end(); ++word_indices) {
			// words that score above the threshold will not be added to the filtered result
			if (dust(word_indices->first, pattern_len) < threshold) {
				filtered_result[name_seqmap->first] = Blastn::IndexedWordMap {
					std::pair<std::string, std::vector<int32_t>>{ word_indices->first, word_indices->second }
				};
			}
		}
	}
	return filtered_result;
}
