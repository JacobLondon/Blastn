#include "test.hpp"
#include "globals.hpp"

void tdust()
{
	std::string words[3] = {
		"AACAACAACAAA",
		"AAAAAAAAAAAA",
		"AGCTCGATGTAG",
	};

	Blastn::DustPatternLength = 3;

	for (auto word : words)
		std::cout << _dust(word, Blastn::DustPatternLength) << std::endl;
}

void textend()
{
	std::string query = "GTCTGAACTGAGC";
	std::string data = "AGTCTGATGACTGGGGAACTCGA";
	std::string word1 = "TC";
	std::string word2 = "CT";

	int32_t qindex1 = query.find(word1);
	int32_t dindex1 = data.find(word1);
	int32_t qindex2 = query.find(word2, qindex1 + word1.size());
	int32_t dindex2 = data.find(word2, dindex1 + word1.size());

	AdjacentPair pair(word1, word2, dindex1, qindex1, dindex2, qindex2);

	std::cout << "Query:\t\t" << query << std::endl;
	std::cout << "Data:\t\t" << data << std::endl;

	Blastn::SwMatch = 2;
	Blastn::SwMismatch = -1;
	Blastn::SwGap = -1;
	Blastn::SwMinscore = 2;
	bool score = true;
	bool printing = true;
	std::string result = _extend_and_score(
		pair,
		query,
		data,
		Blastn::SwMatch,
		Blastn::SwMismatch,
		Blastn::SwGap,
		Blastn::SwMinscore,
		score,
		printing
	);
}

void tmatch()
{
	Blastn::SplitLength = 3;
	Blastn::IndexedSequenceMap query = prepare_sequence("query_small.fa", Blastn::SplitLength, Blastn::Seperator);
	Blastn::IndexedSequenceMap data = prepare_sequence("data_small.fasta", Blastn::SplitLength, Blastn::Seperator);

	Blastn::MatchedSequenceMap m = match_filter(query, data);
	Blastn::print(m);
}

void tsequence()
{
	Blastn::SplitLength = 5;
	Blastn::IndexedSequenceMap s = prepare_sequence("data_small.fasta", Blastn::SplitLength, Blastn::Seperator);
	Blastn::print(s);
}

void tsmith_waterman() {
	std::string seq1 = "ATCGAC";
	std::string seq2 = "ACCGAC";

	Blastn::SwMatch = 2;
	Blastn::SwMismatch = -1;
	Blastn::SwGap = -1;

	int32_t result = smith_waterman(seq1, seq2, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap, false);
}

void tsplit() {
	std::string input = "ATCGAC";
	int32_t length = 3;

	std::vector<std::string> words = split_to_words(input, length);

	std::vector<std::string> result = {
		"ATC",
		"TCG",
		"CGA",
		"GAC"
	};

	if (words == result)
		std::cout << "split.h test passed." << std::endl;
}

