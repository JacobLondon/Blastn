#include <fstream>
#include <sstream>

#include "output.hpp"
#include "../util/display.hpp"

namespace Blastn {

static const string SEPERATOR = "\t\t";

string format_output(vector<HSP>& hsps)
{
    std::ostringstream stream;

    for (auto& hsp : hsps) {
        stream << hsp.query_id      << SEPERATOR
               << hsp.subject_id    << SEPERATOR
               << hsp.percentage_id * 100.0f << SEPERATOR
               << hsp.matches       << SEPERATOR
               << hsp.mismatches    << SEPERATOR
               << hsp.gaps          << SEPERATOR
               << hsp.query_start   << SEPERATOR
               << hsp.query_end     << SEPERATOR
               << hsp.subject_start << SEPERATOR
               << hsp.subject_end   << SEPERATOR
               << hsp.evalue        << SEPERATOR
               << hsp.bitscore       << std::endl;
        /*builder += hsp.query_id   + SEPERATOR;
        builder += hsp.subject_id + SEPERATOR;
        builder += std::to_string(hsp.percentage_id * 100.0f) + SEPERATOR;
        builder += std::to_string(hsp.matches)       + SEPERATOR;
        builder += std::to_string(hsp.mismatches)    + SEPERATOR;
        builder += std::to_string(hsp.gaps)          + SEPERATOR;
        builder += std::to_string(hsp.query_start)   + SEPERATOR;
        builder += std::to_string(hsp.query_end)     + SEPERATOR;
        builder += std::to_string(hsp.subject_start) + SEPERATOR;
        builder += std::to_string(hsp.subject_end)   + SEPERATOR;
        builder += std::to_string(hsp.evalue)        + SEPERATOR;
        builder += std::to_string(hsp.bitscore)      + "\n";
        */
    }
    return stream.str();
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