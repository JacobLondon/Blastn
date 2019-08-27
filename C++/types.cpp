#include "types.hpp"

Match::Match(std::string word, std::vector<int> data_indices, std::vector<int> query_indices)
	: word{word}, data_indices{data_indices}, query_indices{query_indices}
{
	// pass
}
AdjacentPair::AdjacentPair(std::string word1, std::string word2, int dindex1, int qindex1, int dindex2, int qindex2)
	: word1{word1}, word2{word2}, dindex1{dindex1}, qindex1{qindex1}, dindex2{dindex2}, qindex2{qindex2}
{
	length = word1.size();
}
