#include <fstream>
#include "prepare.hpp"
#include "split.hpp"

Blastn::SequenceMap _build_sequence(std::string path, char sep)
{
	Blastn::SequenceMap result;
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

Blastn::IndexedSequenceMap _split_sequence(Blastn::SequenceMap data, int32_t length)
{
	Blastn::IndexedSequenceMap result;

	// traverse the sequence
	for (auto name_seq = data.begin(); name_seq != data.end(); ++name_seq) {
		// get all words and find their indices in that data set
		Blastn::IndexedWordMap indexed_words;
		std::vector<std::string> words = split_to_words(name_seq->second, length);

		// map each word to all of their indices each time the word appears
		for (int32_t i = 0; i < words.size(); i++) {
			// insert the index if the item doesn't exist
			if (indexed_words.find(words[i]) == indexed_words.end()) {
				indexed_words.insert(std::pair<std::string, std::vector<int32_t>>{ words[i], std::vector<int32_t>{ i } });
			}
			// append the index if the item already exists
			else {
				indexed_words.at(words[i]).push_back(i);
			}
		}
		result.insert(std::pair<std::string, Blastn::IndexedWordMap>{ name_seq->first, indexed_words });
	}

	return result;
}

Blastn::IndexedSequenceMap prepare_sequence(std::string path, int32_t length, char sep)
{
	Blastn::SequenceMap built_data = _build_sequence(path, sep);
	Blastn::IndexedSequenceMap indexed_data = _split_sequence(built_data, length);

	return indexed_data;
}
