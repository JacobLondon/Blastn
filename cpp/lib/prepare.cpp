#include <fstream>
#include "prepare.hpp"
#include "split.hpp"

Blastn::SequenceMap build_sequence(string path, char sep)
{
	Blastn::SequenceMap result;
	string name, line;
	std::ifstream sequence_file{ path };

	if (!sequence_file.is_open()) {
		std::cout << "Failure: Could not open: " << path << std::endl;
		exit(-1);
	}

	while (std::getline(sequence_file, line)) {
		// a new sequence name is found
		if (line[0] == sep) {
			// set the new name (sep char is length 1)
			name = line.substr(1, line.length());
			
			// pair the sequence name with an empty build string
			result.insert(std::pair<string, string>{ name, "" });
		}
		// the if statement MUST have been entered first
		else {
			// append the next line of sequence data to the build string
			result.at(name).append(line);
		}
	}

	return result;
}

Blastn::IndexedSequenceMap split_sequence(Blastn::SequenceMap& data, u32 length)
{
	Blastn::IndexedSequenceMap result;

	// traverse the sequence
	for (auto name_seq = data.begin(); name_seq != data.end(); ++name_seq) {
		// get all words and find their indices in that data set
		Blastn::IndexedWordMap indexed_words;
		vector<string> words = split_to_words(name_seq->second, length);

		// map each word to all of their indices each time the word appears
		for (u32 i = 0; i < words.size(); i++) {
			// insert the index if the item doesn't exist
			if (indexed_words.find(words[i]) == indexed_words.end()) {
				indexed_words.insert(std::pair<string, vector<u32>>{ words[i], vector<u32>{ i } });
			}
			// append the index if the item already exists
			else {
				indexed_words.at(words[i]).push_back(i);
			}
		}
		result.insert(std::pair<string, Blastn::IndexedWordMap>{ name_seq->first, indexed_words });
	}

	return result;
}

Blastn::IndexedSequenceMap prepare_sequence(string path, u32 length, char sep)
{
	Blastn::SequenceMap built_data = build_sequence(path, sep);
	Blastn::IndexedSequenceMap indexed_data = split_sequence(built_data, length);

	return indexed_data;
}
