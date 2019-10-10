#include <algorithm>
#include <fstream>
#include "prepare.hpp"
#include "split.hpp"

Blastn::SequenceMap build_sequence(string path, char sep)
{
    Blastn::SequenceMap result;
    string name, line;
    std::ifstream sequence_file{ path };

    if (!sequence_file.is_open()) {
        std::cerr << "Failure: Could not open: " << path << std::endl;
        std::exit(-1);
    }

    while (std::getline(sequence_file, line)) {
        // a new sequence name is found
        if (line[0] == sep) {
            // set the new name (sep char is length 1)
            name = line.substr(1, line.size());
            // no newlines in names
            if (name.rfind('\r') == name.size() - 1)
                name = name.substr(0, name.size() - 1);
            if (name.rfind('\n') == name.size() - 1)
                name = name.substr(0, name.size() - 1);
            
            // pair the sequence name with an empty build string
            result[name] = "";
        }
        // the if statement MUST have been entered first
        else {
            // append the next line of sequence data to the build string
            result[name].append(line);
        }
    }

    return result;
}

Blastn::IndexedSequenceMap split_sequence(Blastn::SequenceMap& data, u32 length)
{
    Blastn::IndexedSequenceMap result;

    // traverse the sequence
    for (auto& name_seqmap : data) {
        // get all words and find their indices in that data set
        Blastn::IndexedWordMap indexed_words;
        vector<string> words = split_to_words(name_seqmap.second, length);

        // map each word to all of their indices each time the word appears
        for (u32 i = 0; i < words.size(); i++) {

            // no newlines in sequences
            string temp = words[i];
            if (temp.rfind('\r') == temp.size() - 1)
                temp = temp.substr(0, temp.size() - 1);
            if (temp.rfind('\n') == temp.size() - 1)
                temp = temp.substr(0, temp.size() - 1);

            // insert the index if the item doesn't exist
            if (indexed_words.find(temp) == indexed_words.end())
                indexed_words[temp] = vector<u32>{};

            // append the index
            indexed_words[temp].push_back(i);
        }
        result[name_seqmap.first] = indexed_words;
    }

    return result;
}

Blastn::IndexedSequenceMap prepare_sequence(string path, u32 length, char sep)
{
    Blastn::SequenceMap built_data = build_sequence(path, sep);
    Blastn::IndexedSequenceMap indexed_data = split_sequence(built_data, length);

    return indexed_data;
}
