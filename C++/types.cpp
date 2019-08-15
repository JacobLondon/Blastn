#include "types.hpp"

Match::Match(std::string word, std::vector<int> data_indices, std::vector<int> query_indices)
	: word{word}, data_indices{data_indices}, query_indices{query_indices}
{
	// pass
}

