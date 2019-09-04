#include "test.hpp"
#include "globals.hpp"

void tdust()
{
	string words[3] = {
		"AACAACAACAAA",
		"AAAAAAAAAAAA",
		"AGCTCGATGTAG",
	};

	Blastn::DustPatternLength = 3;

	for (auto word : words)
		std::cout << dust(word, Blastn::DustPatternLength) << std::endl;
}

void textend()
{
	string query = "GTCTGAACTGAGC";
	string data  = "AGTCTGATGACTGGGGAACTCGA";
	string word1 = "TC";
	string word2 = "CT";

	u32 qindex1 = (u32)query.find(word1);
	u32 dindex1 = (u32)data.find(word1);
	u32 qindex2 = (u32)query.find(word2, qindex1 + word1.size());
	u32 dindex2 = (u32)data.find(word2, dindex1 + word1.size());

	AdjacentPair pair(word1, word2, dindex1, qindex1, dindex2, qindex2);

	std::cout << "Query:\t\t" << query << std::endl;
	std::cout << "Data:\t\t" << data << std::endl;

	Blastn::SwMatch = 2;
	Blastn::SwMismatch = -1;
	Blastn::SwGap = -1;
	Blastn::SwMinscore = 0;
	bool score = true;
	bool printing = true;
	Extended result = extend_and_score(
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

	std::cout << result.extended_pair << std::endl;
}

void tmatch()
{
	Blastn::SplitLength = 3;
	Blastn::IndexedSequenceMap query = prepare_sequence("../data/query_small.fa", Blastn::SplitLength, Blastn::Seperator);
	Blastn::IndexedSequenceMap data = prepare_sequence("../data/data_small.fasta", Blastn::SplitLength, Blastn::Seperator);

	Blastn::MatchedSequenceMap m = match_filter(query, data);
	Blastn::print(m);
}

void tsequence()
{
	Blastn::SplitLength = 5;
	Blastn::IndexedSequenceMap s = prepare_sequence("../data/data_small.fasta", Blastn::SplitLength, Blastn::Seperator);
	Blastn::print(s);
}

void tsmith_waterman() {
	string seq1 = "ATCGAC";
	string seq2 = "ACCGAC";

	Blastn::SwMatch = 2;
	Blastn::SwMismatch = -1;
	Blastn::SwGap = -1;

	u32 result = smith_waterman(seq1, seq2, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap, false);
}

void tsplit() {
	string input = "ATCGAC";
	u32 length = 3;

	vector<string> words = split_to_words(input, length);

	vector<string> result = {
		"ATC",
		"TCG",
		"CGA",
		"GAC"
	};

	if (words == result)
		std::cout << "split test passed." << std::endl;
}
