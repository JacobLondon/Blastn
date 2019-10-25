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

void write_output(string data, string filename)
{
    std::ofstream output_file{ filename };

    if (output_file.is_open()) {
        output_file.write(data.c_str(), data.size());
        output_file.close();
    }
    else {
        std::cerr << "Error: Failed to open output file: " << filename << std::endl;
        std::exit(-1);
    }
}

} // Blastn