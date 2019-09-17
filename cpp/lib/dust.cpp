#include "dust.hpp"
#include "split.hpp"	// split_to_words
#include <algorithm>	// count

f64 dust(string word, u32 pattern_len)
{
	f64 total_score = 0;
	u32 occurrence;
	vector<string> triplets = split_to_words(word, pattern_len);
	dict<string, u32> record;
	// reserve double necessary capacity for hash table to minimize collisions
	record.reserve(triplets.size() * 2);

	for (auto triplet : triplets) {
		// triplet not recorded yet
		if (record.find(triplet) == record.end()) {
			// count occurrences
			occurrence = (u32)std::count(triplets.begin(), triplets.end(), triplet);
			record[triplet] = occurrence * (occurrence - 1) / 2;
		}
	}
	// sum the scores
	for (auto iter = record.begin(); iter != record.end(); ++iter)
		total_score += iter->second;
	// TODO: Remove percentage based modifiers
	return total_score / (word.length() - pattern_len);
}

Blastn::IndexedSequenceMap dust_filter(Blastn::IndexedSequenceMap& data, f64 threshold, u32 pattern_len, u32 word_len)
{
	Blastn::IndexedSequenceMap filtered_result;
	threshold = threshold * (word_len - pattern_len + 1) / 2;
	// TODO: copy format from Python
	// breaks words into subsequences of triplets
	for (auto name_seqmap = data.begin(); name_seqmap != data.end(); ++name_seqmap) {
		for (auto word_indices = name_seqmap->second.begin(); word_indices != name_seqmap->second.end(); ++word_indices) {
			// words that score above the threshold will not be added to the filtered result
			if (dust(word_indices->first, pattern_len) < threshold) {
				filtered_result[name_seqmap->first] = Blastn::IndexedWordMap {
					std::pair<string, vector<u32>>{ word_indices->first, word_indices->second }
				};
			}
		}
	}
	return filtered_result;
}
