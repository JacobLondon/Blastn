#include "match.hpp"
#include "prepare.hpp"

Blastn::MatchedSequenceMap match_filter(Blastn::IndexedSequenceMap& query, Blastn::IndexedSequenceMap& data)
{
	Blastn::MatchedSequenceMap exact_matches;

	// traverse the data IndexedSequenceMap
	for (auto d_name_wordmap = data.begin(); d_name_wordmap != data.end(); ++d_name_wordmap) {
		Blastn::MatchedMatchesMap matches;
		// traverse the query IndexedSequenceMap, create Match objects and insert to exact_matches
		for (auto q_name_wordmap = query.begin(); q_name_wordmap != query.end(); ++q_name_wordmap) {
			for (auto q_word_indices = q_name_wordmap->second.begin();
					  q_word_indices != q_name_wordmap->second.end();
					  ++q_word_indices)
			{
				// ensure data has the query word
				if (d_name_wordmap->second.find(q_word_indices->first) != d_name_wordmap->second.end()) {
					// the current word in the query is also in data but not inserted yet
					if (d_name_wordmap->second.find(q_word_indices->first) == d_name_wordmap->second.end()) {
						matches[q_name_wordmap->first] = vector<Match> {
							Match {
								q_word_indices->first,
								d_name_wordmap->second[q_word_indices->first],
								q_word_indices->second
							} // end of Match initializer
						}; // end of vector<Match> initializer
					}
					// the current word in the query is also in data, and has already been inserted
					else {
						matches[q_name_wordmap->first].emplace_back(
							q_word_indices->first,
							d_name_wordmap->second[q_word_indices->first],
							q_word_indices->second
						);
					}
				}
			} // end word_indices
		} // end query map

		// record if there were matches found
		if (!matches.empty())
			exact_matches.insert(std::pair<string, Blastn::MatchedMatchesMap>{ d_name_wordmap->first, matches });
	} // end data map

	return exact_matches;
}
