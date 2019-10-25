#include <fstream>
#include "output.hpp"
#include "../util/display.hpp"

namespace Blastn {

string format_output(vector<HSP>& hsps, SequenceMap& subject)
{
    string builder = "";
    for (auto& hsp : hsps) {
        builder += hsp.query_id   + "\t";
        builder += hsp.subject_id + "\t";
        builder += std::to_string(hsp.percentage_id * 100) + "\t";
        builder += std::to_string(hsp.matches)       + "\t";
        builder += std::to_string(hsp.mismatches)    + "\t";
        builder += std::to_string(hsp.gaps)          + "\t";
        builder += std::to_string(hsp.query_start)   + "\t";
        builder += std::to_string(hsp.query_end)     + "\t";
        builder += std::to_string(hsp.subject_start) + "\t";
        builder += std::to_string(hsp.subject_end)   + "\t";
        builder += std::to_string(hsp.evalue)        + "\t";
        builder += std::to_string(hsp.bitscore)      + "\n";
    }
    return builder;
}

void write_output(string data, string output_file)
{
    for (auto& qname_output : output) {
        string filename = "Hits-" + qname_output.first + extension;
        std::ofstream output_file;

        if (success)
            output_file = std::ofstream{ dirname + "/" + filename };
        else
            output_file = std::ofstream{ filename };

        if (output_file.is_open()) {
            output_file.write(qname_output.second.c_str(), qname_output.second.size());
            output_file.close();
        }
        else {
            std::cerr << "Error: Failed to open output file " << qname_output.first << std::endl;
            std::exit(-1);
        }
    }
}

} // Blastn