#include <fstream>
#include "output.hpp"
#include "../util/display.hpp"

namespace Blastn {

FormattedSequenceMap format_data(ExtendedSequenceMap& extended_pairs)
{
    FormattedSequenceMap result;
    Progress progress { extended_pairs.size() };

    // move dname into each extended pair
    for (auto& dname_queries : extended_pairs) {
        for (auto& qname_epairs : dname_queries.second) {
            if (result.find(qname_epairs.first) == result.end())
                result[qname_epairs.first] = vector<Formatted>{};
            for (auto& epair : qname_epairs.second) {
                result[qname_epairs.first].emplace_back(
                    dname_queries.first,
                    epair.extended_pair,
                    epair.dindex,
                    epair.qindex,
                    epair.score
                );
            }
        }
    }
    return result;
}

string format_output(FormattedSequenceMap& s, SequenceMap& data)
{
    string builder = "";
    for (auto& qname_fpairs : s) {
        for (auto& fpair : qname_fpairs.second) {
            builder += "\n";
            builder += "Smith-Waterman Score : " + std::to_string(fpair.score) + "\n";
            builder += "Hit at " + fpair.dname + "[" + std::to_string(fpair.dindex) + "]:\n\t";
            builder += data[fpair.dname].substr(fpair.dindex, fpair.extended_pair.size()) + "\n";
            builder += "Match at " + qname_fpairs.first + "[" + std::to_string(fpair.qindex) + "]\n";
            builder += "Extended HSP:\n\t" + fpair.extended_pair + "\n";
        }
    }
    return builder;
}

void write_output(string& output, string filename)
{
    std::ofstream output_file{ filename };
    output_file << output;
    output_file.close();
}

} // Blastn