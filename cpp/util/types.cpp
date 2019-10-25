#include "types.hpp"

namespace Blastn {

Match::Match(string word, vector<u32> subject_indices, vector<u32> query_indices)
    : word{ word }, subject_indices{ subject_indices }, query_indices{ query_indices }
{}

AdjacentPair::AdjacentPair(string word1, string word2, u32 dindex1, u32 qindex1, u32 dindex2, u32 qindex2)
    : word1{ word1 }, word2{ word2 }, sindex1{ dindex1 }, sindex2{ dindex2 }, qindex1{ qindex1 }, qindex2{ qindex2 }
{
    length = (u32)word1.size();
}

Extended::Extended(string extended_pair, u32 dindex, u32 qindex, s32 score)
    : extended_pair{ extended_pair }, sindex{ dindex }, qindex{ qindex }, score{ score }
{}

HSP::HSP(string subject_id, string query_id, string extended_pair, u32 sindex, u32 qindex, s32 sw_score)
    : subject_id{ subject_id }, query_id{ query_id }, extended_pair{ extended_pair },
      subject_start{ sindex },  subject_end{ sindex + extended_pair.size() },
      query_start{ qindex },    query_end{ qindex + extended_pair.size() },
      sw_score{ sw_score }
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
                builder += "\tSubject Indices:  " + str(match.subject_indices);
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
        builder += "Subject Index: "  + std::to_string(e.sindex) + ", ";
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

string str(vector<HSP> hsps)
{
    string builder = "";
    for (auto& hsp : hsps) {
            builder += hsp.subject_id;
            builder += "{ Ext Pair: "  + hsp.extended_pair + ", ";
            builder += "Subject Index: "  + std::to_string(hsp.subject_start) + ", ";
            builder += "Query Index: " + std::to_string(hsp.query_start) + " }, ";
    }
    return builder;
}

} // Blastn