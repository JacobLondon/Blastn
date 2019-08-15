#include <iostream>
#include "match.hpp"
#include "prepare.hpp"

Blastn::MatchedSequenceMap match_filter(Blastn::IndexedSequenceMap query, Blastn::IndexedSequenceMap data)
{
	Blastn::MatchedSequenceMap exact_matches;

	// traverse the data IndexedSequenceMap
	for (auto d_name_wordmap = data.begin(); d_name_wordmap != data.end(); ++d_name_wordmap) {
		Blastn::MatchedMatchesMap matches;
		// traverse the query IndexedSequenceMap, create Match objects and insert to exact_matches
		for (auto q_name_wordmap = query.begin(); q_name_wordmap != query.end(); ++q_name_wordmap) {
			for (auto q_word_indices = q_name_wordmap->second.begin();
					  q_word_indices != q_name_wordmap->second.end();
					  ++q_word_indices) {
				// the current word in the query is also in data but not inserted yet
				if (d_name_wordmap->second.find(q_word_indices->first) == d_name_wordmap->second.end()) {
					matches.insert(std::pair<std::string, std::vector<Match>> {
						q_name_wordmap->first,
						std::vector<Match> { Match { q_word_indices->first,
													 d_name_wordmap->second.at(q_word_indices->first),
													 q_word_indices->second } // end of Match initializer
						} // end of vector<Match> initializer
					}); // end of pair initializer
				}
				// the current word in the query is also in data, and has already been inserted
				else {
					matches.at(q_name_wordmap->first)
						   .emplace_back(q_word_indices->first,
										 d_name_wordmap->second.at(q_word_indices->first),
										 q_word_indices->second);
				}
			}
		}
		// record if there were matches found
		if (!matches.empty())
			exact_matches.insert(std::pair<std::string, Blastn::MatchedMatchesMap>{ d_name_wordmap->first, matches });
	}
	return exact_matches;
}

void print(Blastn::MatchedSequenceMap m)
{
	for (auto d_name_quermap = m.begin(); d_name_quermap != m.end(); ++d_name_quermap) {
		for (auto q_name_matchvec = d_name_quermap->second.begin();
				  q_name_matchvec != d_name_quermap->second.end();
				  ++q_name_matchvec) {
			for (int i = 0; i < q_name_matchvec->second.size(); i++) {
				std::cout << q_name_matchvec->second[i].word << "\t";
				std::cout << d_name_quermap->first << "[";
				for (int j = 0; j < q_name_matchvec->second[i].data_indices.size(); j++)
					std::cout << q_name_matchvec->second[i].data_indices[j] << ". ";
				std::cout << "]\t";
				std::cout << q_name_matchvec->first << "[";
				for (int j = 0; j < q_name_matchvec->second[i].query_indices.size(); j++)
					std::cout << q_name_matchvec->second[i].query_indices[j] << ". ";
				std::cout << "]" << std::endl;
			}
		}
	}
}

void test_match()
{
	Blastn::IndexedSequenceMap query = prepare_sequence("query_small.fa", 3, '>');
	Blastn::IndexedSequenceMap data = prepare_sequence("data_small.fasta", 3, '>');

	Blastn::MatchedSequenceMap m = match_filter(query, data);
	print(m);
}
