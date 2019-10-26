#include <fstream>
#include "output.hpp"
#include "../util/display.hpp"

namespace Blastn {

static const string SEPERATOR = "\t\t";

string format_output(vector<HSP>& hsps)
{
    string builder = "";
    for (auto& hsp : hsps) {
        builder += hsp.query_id   + SEPERATOR;
        builder += hsp.subject_id + SEPERATOR;
        builder += std::to_string(hsp.percentage_id * 100) + SEPERATOR;
        builder += std::to_string(hsp.matches)       + SEPERATOR;
        builder += std::to_string(hsp.mismatches)    + SEPERATOR;
        builder += std::to_string(hsp.gaps)          + SEPERATOR;
        builder += std::to_string(hsp.query_start)   + SEPERATOR;
        builder += std::to_string(hsp.query_end)     + SEPERATOR;
        builder += std::to_string(hsp.subject_start) + SEPERATOR;
        builder += std::to_string(hsp.subject_end)   + SEPERATOR;
        builder += std::to_string(hsp.evalue)        + SEPERATOR;
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