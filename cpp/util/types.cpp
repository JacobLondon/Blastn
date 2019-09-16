#include "types.hpp"

Match::Match(string word, vector<u32> data_indices, vector<u32> query_indices)
	: word{ word }, data_indices{ data_indices }, query_indices{ query_indices }
{
	// pass
}
AdjacentPair::AdjacentPair(string word1, string word2, u32 dindex1, u32 qindex1, u32 dindex2, u32 qindex2)
	: word1{ word1 }, word2{ word2 }, dindex1{ dindex1 }, qindex1{ qindex1 }, dindex2{ dindex2 }, qindex2{ qindex2 }
{
	length = (u32)word1.size();
}

Extended::Extended(string extended_pair, s32 dindex)
	: extended_pair{ extended_pair }, dindex{ dindex }
{
	// pass
}

Sorted::Sorted(string extended_pair, s32 dindex, s32 score)
	: extended_pair{ extended_pair }, dindex{ dindex }, score{ score }
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
				for (u32 i = 0; i < words_indices->second.size(); i++) {
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
				for (u32 i = 0; i < q_name_matchvec->second.size(); i++) {
					std::cout << q_name_matchvec->second[i].word << "\t" << d_name_quermap->first << "[";
					for (u32 j = 0; j < q_name_matchvec->second[i].data_indices.size(); j++) {
						std::cout << q_name_matchvec->second[i].data_indices[j] << ". ";
					}
					std::cout << "]\t" << q_name_matchvec->first << "[";
					for (u32 j = 0; j < q_name_matchvec->second[i].query_indices.size(); j++) {
						std::cout << q_name_matchvec->second[i].query_indices[j] << ". ";
					}
					std::cout << "]" << std::endl;
				}
			}
		}
	}

	void print(PairedSequenceMap m)
	{
		for (auto d_name_quermap = m.begin(); d_name_quermap != m.end(); ++d_name_quermap) {
			for (auto q_name_pairvec = d_name_quermap->second.begin();
				q_name_pairvec != d_name_quermap->second.end();
				++q_name_pairvec) {
				for (u32 i = 0; i < q_name_pairvec->second.size(); i++) {
					std::cout << "Word 1: " << q_name_pairvec->second[i].word1 << "\t";
					std::cout << "Word 2: " << q_name_pairvec->second[i].word2 << "\t";
					std::cout << "Length: " << q_name_pairvec->second[i].length << "\t";
					std::cout << std::endl;
				}
			}
		}
	}

	void print(ExtendedSequenceMap m)
	{
		for (auto d_name_quermap = m.begin(); d_name_quermap != m.end(); ++d_name_quermap) {
			for (auto q_name_extendedvec = d_name_quermap->second.begin();
				q_name_extendedvec != d_name_quermap->second.end();
				++q_name_extendedvec) {
				for (u32 i = 0; i < q_name_extendedvec->second.size(); i++) {
					std::cout << "Extended Pair: " << q_name_extendedvec->second[i].extended_pair << "\t";
					std::cout << "Data Index: " << q_name_extendedvec->second[i].dindex << "\t";
					std::cout << std::endl;
				}
			}
		}
	}
	
	void print(SortedSequenceMap m)
	{
		for (auto d_name_quermap = m.begin(); d_name_quermap != m.end(); ++d_name_quermap) {
			for (auto q_name_sortedvec = d_name_quermap->second.begin();
				q_name_sortedvec != d_name_quermap->second.end();
				++q_name_sortedvec) {
				for (u32 i = 0; i < q_name_sortedvec->second.size(); i++) {
					std::cout << "Extended Pair: " << q_name_sortedvec->second[i].extended_pair << "\t";
					std::cout << "Data Index: " << q_name_sortedvec->second[i].dindex << "\t";
					std::cout << "SW Score: " << q_name_sortedvec->second[i].score << "\t";
					std::cout << std::endl;
				}
			}
		}
	}
}
