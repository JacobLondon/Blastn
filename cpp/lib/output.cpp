#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <errno.h>
#endif
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

SequenceMap format_output(FormattedSequenceMap& s, SequenceMap& data)
{
    SequenceMap result;
    for (auto& qname_fpairs : s) {
        string builder = "";
        for (auto& fpair : qname_fpairs.second) {
            builder += "\n";
            builder += "Smith-Waterman Score : " + std::to_string(fpair.score) + "\n";
            builder += "Hit at " + fpair.dname + "[" + std::to_string(fpair.dindex) + "]:\n\t";
            builder += data[fpair.dname].substr(fpair.dindex, fpair.extended_pair.size()) + "\n";
            builder += "Match at " + qname_fpairs.first + "[" + std::to_string(fpair.qindex) + "]\n";
            builder += "Extended HSP:\n\t" + fpair.extended_pair + "\n";
        }
        result[qname_fpairs.first] = builder;
    }
    return result;
}

static bool make_dir(string dirname)
{
    bool success = false;

    #ifdef _WIN32
        int status = mkdir(dirname.c_str());
        if (status == 0)
            success = true;
    #else
        DIR* dir = opendir(dirname.c_str());
        if (dir) {
            // directory exists
            closedir(dir);
            success = true;
        }
        else if (ENOENT == errno) {
            // directory does not
            int status = -1;
            status = mkdir(dirname.c_str(), 0700);
            if (status == 0)
                success = true;
        }
        else {
            // success remains false
        }
   #endif

    if (!success) {
        std::cerr << "Error: Failed to create output directory."
                  << " Dumping output files in current directory instead..." << std::endl;
        return false;
    }
    return true;
}

void write_output(SequenceMap& output, string dirname, string extension)
{
    bool success = make_dir(dirname);

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