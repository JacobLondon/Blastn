#include "types.hpp"

namespace Blastn {

Match::Match(string word, vector<u32> data_indices, vector<u32> query_indices)
    : word{ word }, data_indices{ data_indices }, query_indices{ query_indices }
{}

AdjacentPair::AdjacentPair(string word1, string word2, u32 dindex1, u32 qindex1, u32 dindex2, u32 qindex2)
    : word1{ word1 }, word2{ word2 }, dindex1{ dindex1 }, dindex2{ dindex2 }, qindex1{ qindex1 }, qindex2{ qindex2 }
{
    length = (u32)word1.size();
}

Extended::Extended(string extended_pair, u32 dindex, u32 qindex, s32 score)
    : extended_pair{ extended_pair }, dindex{ dindex }, qindex{ qindex }, score{ score }
{}

string str(Matrix m) {
    string builder = "";
    for (auto v : m) {
        for (auto score : v) {
            builder += std::to_string(score) + ". ";
        }
        builder += "\n";
    }
    builder += "\n";
    return builder;
}

string str(SequenceMap s)
{
    string builder = "";
    for (auto& name_seq : s)
        builder += name_seq.first + ": " + name_seq.second + "\n";
    return builder;
}

static string str(vector<u32> ints)
{
    string builder = "[";
    for (auto& i : ints)
        builder += std::to_string(i) + ". ";
    builder += "]";
    return builder;
}

string str(IndexedSequenceMap s)
{
    string builder = "";
    for (auto& dname_queries : s) {
        for (auto& qname_indices : dname_queries.second) {
            builder += dname_queries.first + "\t" + qname_indices.first;
            builder += str(qname_indices.second) + "\n";
        }
    }
    return builder;
}

string str(MatchedSequenceMap s)
{
    string builder = "";
    for (auto& dname_queries : s) {
        for (auto& qname_matches : dname_queries.second) {
            for (auto& match : qname_matches.second) {
                builder += dname_queries.first + "\t" + qname_matches.first;
                builder += "\t" + match.word;
                builder += "\tData Indices:  " + str(match.data_indices);
                builder += "\tMatch Indices: " + str(match.query_indices) + "\n";
            }
        }
    }
    return builder;
}

static string str(vector<AdjacentPair> pairs)
{
    string builder = "[";
    for (auto& p : pairs) {
        builder += "{ Word 1: " + p.word1 + ", ";
        builder += "Word 2: " + p.word2 + ", ";
        builder += "Length: " + std::to_string(p.length) + " }, ";
    }
    builder += "]";
    return builder;
}

string str(PairedSequenceMap s)
{
    string builder = "";
    for (auto& dname_queries : s) {
        for (auto& qname_pairs : dname_queries.second) {
            builder += dname_queries.first + "\t" + qname_pairs.first;
            builder += str(qname_pairs.second) + "\n";
        }
    }
    return builder;
}

static string str(vector<Extended> ext)
{
    string builder = "[";
    for (auto& e : ext) {
        builder += "{ Ext Pair: "  + e.extended_pair          + ", ";
        builder += "Data Index: "  + std::to_string(e.dindex) + ", ";
        builder += "Query Index: " + std::to_string(e.qindex) + " }, ";
    }
    builder += "]";
    return builder;
}

string str(ExtendedSequenceMap s)
{
    string builder = "";
    for (auto& dname_queries : s) {
        for (auto& qname_ext : dname_queries.second) {
            builder += dname_queries.first + "\t" + qname_ext.first;
            builder += str(qname_ext.second) + "\n";
        }
    }
    return builder;
}

string output_format(ExtendedSequenceMap& s, SequenceMap& data)
{
    string builder = "";
    for (auto& dname_queries : s) {
        for (auto& qname_epairs : dname_queries.second) {
            for (auto& epair : qname_epairs.second) {
                builder += "\n";
                builder += "Smith-Waterman Score : " + std::to_string(epair.score) + "\n";
                builder += "Hit at " + dname_queries.first + "[" + std::to_string(epair.dindex) + "]:\n\t";
                builder += data[dname_queries.first].substr(epair.dindex, epair.extended_pair.size()) + "\n";
                builder += "Match at " + qname_epairs.first + "[" + std::to_string(epair.qindex) + "]\n";
                builder += "Extended HSP:\n\t" + epair.extended_pair + "\n";
            }
        }
    }
    return builder;
}

} // Blastn