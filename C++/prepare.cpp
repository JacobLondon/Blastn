#include <fstream>
#include <iostream>
#include "prepare.hpp"


SequenceMap _build_sequence(std::string path, char sep)
{
	SequenceMap result;
	std::string name, line;
	std::ifstream sequence_file{ path };

	while (std::getline(sequence_file, line)) {
		// a new sequence name is found
		if (line[0] == sep) {
			// set the new name (sep char is length 1)
			name = line.substr(1, line.length());
			
			// pair the sequence name with an empty build string
			result.insert(std::pair<std::string, std::string>{ name, "" });
		}
		// the if statement MUST have been entered first
		else {
			// append the next line of sequence data to the build string
			result.at(name).append(line);
		}
	}

	return result;
}

IndexedSequenceMap _split_sequence(SequenceMap data, int length)
{
	IndexedSequenceMap result;
	int i;

	// traverse the sequence
	for (auto iter = data.begin(); iter != data.end(); ++iter) {
		// get all words and find their indices in that data set
		std::unordered_map<std::string, std::vector<int>> indexed_words;
		std::vector<std::string> words = split_to_words(iter->second, length);

		// map each word to all of their indices each time the word appears
		for (i = 0; i < words.size(); i++) {
			// insert the index if the item doesn't exist
			if (indexed_words.find(words[i]) == indexed_words.end()) {
				indexed_words.insert(std::pair<std::string, std::vector<int>>{ words[i], std::vector<int>{ i } });
			}
			// append the index if the item already exists
			else {
				indexed_words.at(words[i]).push_back(i);
			}
		}
	}

	return result;
}

IndexedSequenceMap prepare_sequence(std::string path, int length, char sep)
{
	SequenceMap built_data = _build_sequence(path, sep);
	IndexedSequenceMap indexed_data = _split_sequence(built_data, length);

	return indexed_data;
}

void print_sequence_map(SequenceMap s)
{
	for (auto iter = s.begin(); iter != s.end(); ++iter) {
		std::cout << iter->first << ": " << iter->second << std::endl;
	}
}

void print_indexed_sequence_map(IndexedSequenceMap s)
{
	// traverse names mapped to words
	for (auto name_data = s.begin(); name_data != s.end(); ++name_data) {
		std::cout << "\n" << name_data->first << ": ";
		// traverse words mapped to indices
		for (auto words_indices = name_data->second.begin(); words_indices != name_data->second.end(); ++words_indices) {
			std::cout << words_indices->first << ": {";
			// traverse vector of indices
			for (int i = 0; i < words_indices->second.size(); i++) {
				std::cout << words_indices->second[i] << ". ";
			}
			std::cout << "}";
		}
	}
	std::cout << std::endl;
}

void test_sequence()
{
	IndexedSequenceMap s = prepare_sequence("data_small.fasta", 5, '>');
	print_indexed_sequence_map(s);
}
