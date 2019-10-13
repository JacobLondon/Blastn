#include <chrono>
#include <ctime>
#include <fstream>
#include "blastn.hpp"
#include "../util/globals.hpp"
#include "../util/test.hpp"

namespace Blastn {

static std::string argparse(vector<string> arguments, std::string arg)
{
    for (size_t i = 0; i < arguments.size(); i++) {
        if (arg == arguments[i]) {
            if (i + 1 >= arguments.size()) {
                std::cerr << "Failure: Invalid argument usage: " << arg << std::endl;
                std::exit(-1);
            }
            else
                return arguments[i + 1];
        }
    }
    return Blastn::Invalid;
}

int test(std::vector<std::string> args)
{
    string a;
    a = argparse(args, "-test");
    if (a == Blastn::Invalid) {
        std::cerr << "Error: Unknown test function argument." << std::endl;
        std::exit(-1);
    }
    
    if (a == "dust")
        Test::dust();
    else if (a == "extend")
        Test::extend();
    else if (a == "match")
        Test::match();
    else if (a == "pairs")
        Test::pairs();
    else if (a == "sequence")
        Test::sequence();
    else if (a == "sw" || a == "smith waterman")
        Test::smith_waterman();
    else if (a == "sort")
        Test::sort();
    else if (a == "split")
        Test::split();
    else
        std::cout << "Unknown test function: " << a << std::endl;

    return 0;
}

static void align(std::string query_file, std::string data_file)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto start_time = std::chrono::system_clock::now();
    std::time_t start_timestamp = std::chrono::system_clock::to_time_t(start_time);
    std::cout << "Blastn started on " << std::ctime(&start_timestamp) << std::endl;

    /**
     * Data formatting
     */

    std::cout << "Reading " << query_file << "..." << std::endl;
    auto query = Blastn::build_sequence(query_file, Blastn::Seperator);
    std::cout << "Formatting " << query.size() << " query entries..." << std::endl;
    auto query_prepared = Blastn::split_sequence(query, Blastn::SplitLength);
    std::cout << std::endl;

    std::cout << "Reading " << data_file << "..." << std::endl;
    auto data = Blastn::build_sequence(data_file, Blastn::Seperator);
    std::cout << "Formatting " << data.size() << " database entries..." << std::endl;
    auto data_prepared = Blastn::split_sequence(data, Blastn::SplitLength);
    std::cout << std::endl;

    /**
     * Dust filtering
     */

    std::cout << "Dust Complexity Filtering " << query.size() << " query entries..." << std::endl;
    auto query_dustfiltered = Blastn::dust_filter(query_prepared, Blastn::DustThreshold, Blastn::DustPatternLength);

    std::cout << std::endl;

    /**
     * Exact matches, adjacent pairs, extending pairs, and sorting extended pairs
     * all on smaller data subsets
     */

    std::cout << "Matching " << query.size() << " query entries against " << data.size() << " database entries..." << std::endl;
    auto exact_matches = Blastn::match_filter(query_dustfiltered, data_prepared);
    std::cout << std::endl;

    std::cout << "Pairing " << exact_matches.size() << " words with each other..." << std::endl;
    auto adjacent_pairs = Blastn::pair_filter(exact_matches, query);
    std::cout << std::endl;

    std::cout << "Extending " << adjacent_pairs.size() << " paired words..." << std::endl;
    auto extended_pairs = Blastn::extend_filter(adjacent_pairs, query, data, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap, Blastn::SwRatio);
    std::cout << std::endl;

    std::cout << "Sorting " << extended_pairs.size() << " extended pairs..." << std::endl;
    auto sorted_epairs = Blastn::sort_filter(extended_pairs, query, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);
    std::cout << std::endl;

    std::cout << std::endl;

    /**
     * Blastn finished, write to file
     */

    std::cout << "Writing to file " << Blastn::OutputFile << "..." << std::endl;
    std::ofstream output_file{ Blastn::OutputFile };
    output_file << Blastn::output_format(sorted_epairs, data);

    std::cout << std::endl;

    /**
     * Timer stats
     */

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<f32> elapsed = end - start;
    auto end_time = std::chrono::system_clock::now();
    std::time_t end_timestamp = std::chrono::system_clock::to_time_t(end_time);
    std::cout << "Blastn finished on " << std::ctime(&end_timestamp) << "Elapsed time: " << elapsed.count() << "s." << std::endl;
}

int blastn(std::vector<std::string> args)
{
    // arg output
    string a;

    // input files
    a = argparse(args, "-q");
    if (a != Blastn::Invalid) Blastn::QueryFile         = a;
    a = argparse(args, "-db");
    if (a != Blastn::Invalid) Blastn::DataFile          = a;

    // optional arguments (have defaults)
    a = argparse(args, "-sp");
    if (a != Blastn::Invalid) Blastn::Seperator         = (char)a[0];
    a = argparse(args, "-l");
    if (a != Blastn::Invalid) Blastn::SplitLength       = atoi(a.c_str());
    a = argparse(args, "-m");
    if (a != Blastn::Invalid) Blastn::SwMinscore        = atoi(a.c_str());
    a = argparse(args, "-ma");
    if (a != Blastn::Invalid) Blastn::SwMatch           = atoi(a.c_str());
    a = argparse(args, "-mi");
    if (a != Blastn::Invalid) Blastn::SwMismatch        = atoi(a.c_str());
    a = argparse(args, "-g");
    if (a != Blastn::Invalid) Blastn::SwGap             = atoi(a.c_str());
    a = argparse(args, "-dt");
    if (a != Blastn::Invalid) Blastn::DustThreshold     = (f32)atof(a.c_str());
    a = argparse(args, "-dl");
    if (a != Blastn::Invalid) Blastn::DustPatternLength = atoi(a.c_str());
    a = argparse(args, "-o");
    if (a != Blastn::Invalid) Blastn::OutputFile        = a;

    Blastn::SwRatio = (f32)SwMinscore / (f32)(SplitLength * SwMatch);

    align(Blastn::QueryFile, Blastn::DataFile);
    return 0;
}

} // Blastn