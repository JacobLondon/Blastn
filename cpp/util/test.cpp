#include "../lib/blastn.hpp"
#include "test.hpp"
#include "globals.hpp"

namespace Blastn::Test {

void dust()
{
    string words[3] = {
        "AACAACAACAAA",
        "AAAAAAAAAAAA",
        "AGCTCGATGTAG",
    };

    Blastn::DustPatternLength = 3;

    for (auto word : words)
        std::cout << Blastn::dust(word, Blastn::DustPatternLength) << std::endl;
}

void extend()
{
    string query = "GTCTGAACTGAGC";
    string data  = "AGTCTGATGACTGGGGAACTCGA";
    string word1 = "TC";
    string word2 = "CT";

    u32 qindex1 = (u32)query.find(word1);
    u32 dindex1 = (u32)data.find(word1);
    u32 qindex2 = (u32)query.find(word2, qindex1 + word1.size());
    u32 dindex2 = (u32)data.find(word2, dindex1 + word1.size());

    Blastn::AdjacentPair pair(word1, word2, dindex1, qindex1, dindex2, qindex2);

    std::cout << "Query:\t\t" << query << std::endl;
    std::cout << "Data:\t\t" << data << std::endl;

    Blastn::SwMatch = 2;
    Blastn::SwMismatch = -1;
    Blastn::SwGap = -1;
    Blastn::SwMinscore = 0;
    bool score = true;
    bool printing = true;
    Blastn::Extended result = extend_and_score(
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

void match()
{
    Blastn::SplitLength = 3;
    Blastn::IndexedSequenceMap query = Blastn::prepare_sequence("../data/query_small.fa", Blastn::SplitLength, Blastn::Seperator);
    Blastn::IndexedSequenceMap data = Blastn::prepare_sequence("../data/data_small.fasta", Blastn::SplitLength, Blastn::Seperator);

    Blastn::MatchedSequenceMap m = Blastn::match_filter(query, data);
    std::cout << Blastn::str(m) << std::endl;
}

void pairs()
{
    string qpath = "../data/query_small.fa";
    string dpath = "../data/data_small.fasta";
    u32 length = 3;

    auto query = prepare_sequence(qpath, length, Seperator);
    auto data = prepare_sequence(dpath, length, Seperator);

    auto matches = match_filter(query, data);

    if (matches.empty()) {
        std::cout << "No matches found" << std::endl;
        return;
    }

    std::cout << str(matches) << std::endl;

    auto pairs = pair_filter(matches, build_sequence(qpath, Seperator));
    std::cout << str(pairs) << std::endl;
}

void sequence()
{
    Blastn::SplitLength = 5;
    Blastn::IndexedSequenceMap s = Blastn::prepare_sequence("../data/data_small.fasta", Blastn::SplitLength, Blastn::Seperator);
    std::cout << Blastn::str(s) << std::endl;
}

void smith_waterman()
{
    string seq1 = "ATCGAC";
    string seq2 = "ACCGAC";

    Blastn::SwMatch = 2;
    Blastn::SwMismatch = -1;
    Blastn::SwGap = -1;

    u32 result = Blastn::smith_waterman(seq1, seq2, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap, false);
    std::cout << result << std::endl;
}

void sort()
{

}

void split()
{
    string input = "ATCGAC";
    u32 length = 3;

    vector<string> words = Blastn::split_to_words(input, length);

    vector<string> result = {
        "ATC",
        "TCG",
        "CGA",
        "GAC"
    };

    if (words == result)
        std::cout << "split test passed." << std::endl;
}

} // Blastn::Test