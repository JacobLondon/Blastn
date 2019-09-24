#include "match.hpp"
#include "prepare.hpp"

Blastn::MatchedSequenceMap match_filter(Blastn::IndexedSequenceMap& query, Blastn::IndexedSequenceMap& data)
{
	Blastn::MatchedSequenceMap exact_matches;

	// traverse the data IndexedSequenceMap
    for (auto& dname_wordmap : data) {
		Blastn::MatchedMatchesMap matches;
		// traverse the query IndexedSequenceMap, create Match objects and insert to exact_matches
        for (auto& qname_wordmap : query) {
            for (auto& qword_indices : qname_wordmap.second) {
				// skip if the data doesn't have query word
                if (dname_wordmap.second.find(qword_indices.first) == dname_wordmap.second.end())
                    continue;
				// the current word in the query is also in data but not inserted yet
				if (dname_wordmap.second.find(qword_indices.first) == dname_wordmap.second.end()) {
					matches[qname_wordmap.first] = vector<Match> {
                        Match {
                            qword_indices.first,
						    dname_wordmap.second[qword_indices.first],
						    qword_indices.second
						} // end of Match initializer
					}; // end of vector<Match> initializer
				}
				// the current word in the query is also in data, and has already been inserted
				else {
					matches[qname_wordmap.first].emplace_back(
						qword_indices.first,
						dname_wordmap.second[qword_indices.first],
						qword_indices.second
					);
				}
			} // end word_indices
		} // end query map

		// record if there were matches found
		if (!matches.empty())
            exact_matches[dname_wordmap.first] = matches;
	} // end data map

	return exact_matches;
}
