#include "types.hpp"

Match::Match(std::string word, std::vector<int32_t> data_indices, std::vector<int32_t> query_indices)
	: word{ word }, data_indices{ data_indices }, query_indices{ query_indices }
{
	// pass
}
AdjacentPair::AdjacentPair(std::string word1, std::string word2, int32_t dindex1, int32_t qindex1, int32_t dindex2, int32_t qindex2)
	: word1{ word1 }, word2{ word2 }, dindex1{ dindex1 }, qindex1{ qindex1 }, dindex2{ dindex2 }, qindex2{ qindex2 }
{
	length = word1.size();
}

Extended::Extended(std::string extended_pair, int32_t dindex)
	: extended_pair{ extended_pair }, dindex{ dindex }
{
	// pass
}

namespace Blastn {

	void print(Matrix m) {
		for (auto v : m) {
			for (auto score : v) {
				std::cout << score << ". ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
	}


	void print(SequenceMap s)
	{
		for (auto iter = s.begin(); iter != s.end(); ++iter) {
			std::cout << iter->first << ": " << iter->second << std::endl;
		}
	}

	void print(IndexedSequenceMap s)
	{
		// traverse names mapped to words
		for (auto name_data = s.begin(); name_data != s.end(); ++name_data) {
			std::cout << "\n" << name_data->first << ":\n";
			// traverse words mapped to indices
			for (auto words_indices = name_data->second.begin(); words_indices != name_data->second.end(); ++words_indices) {
				std::cout << "\t" << words_indices->first << ": [";
				// traverse vector of indices
				for (int32_t i = 0; i < words_indices->second.size(); i++) {
					std::cout << words_indices->second[i] << ". ";
				}
				std::cout << "]\n";
			}
		}
		std::cout << std::endl;
	}

	void print(MatchedSequenceMap m)
	{
		for (auto d_name_quermap = m.begin(); d_name_quermap != m.end(); ++d_name_quermap) {
			for (auto q_name_matchvec = d_name_quermap->second.begin();
				q_name_matchvec != d_name_quermap->second.end();
				++q_name_matchvec) {
				for (int32_t i = 0; i < q_name_matchvec->second.size(); i++) {
					std::cout << q_name_matchvec->second[i].word << "\t" << d_name_quermap->first << "[";
					for (int32_t j = 0; j < q_name_matchvec->second[i].data_indices.size(); j++) {
						std::cout << q_name_matchvec->second[i].data_indices[j] << ". ";
					}
					std::cout << "]\t" << q_name_matchvec->first << "[";
					for (int32_t j = 0; j < q_name_matchvec->second[i].query_indices.size(); j++) {
						std::cout << q_name_matchvec->second[i].query_indices[j] << ". ";
					}
					std::cout << "]" << std::endl;
				}
			}
		}
	}
}
