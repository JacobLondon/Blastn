#define TEST false

#if TEST == false

#include <chrono>
#include <fstream>
#include "util/globals.hpp"
#include "lib/blastn.hpp"

static std::string argparse(int argc, char **argv, std::string arg)
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
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

static void blastn(std::string query_file, std::string data_file)
{
    auto start = std::chrono::high_resolution_clock::now();

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
     * Smith Waterman and Dust filtering
     */

    std::cout << "Smith-Waterman Filtering " << query.size() << " query entries..." << std::endl;
    auto query_swfiltered = Blastn::smith_waterman_filter(query_prepared, Blastn::SwMinscore, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);
    //std::cout << Blastn::str(query_swfiltered);

    std::cout << "Dust Complexity Filtering " << query.size() << " query entries..." << std::endl;
    auto query_dustfiltered = Blastn::dust_filter(query_swfiltered, Blastn::DustThreshold, Blastn::DustPatternLength);
    //std::cout << Blastn::str(query_dustfiltered);

    std::cout << std::endl;

    /**
     * Exact matches, adjacent pairs, extending pairs, and sorting extended pairs
     * all on smaller data subsets
     */

    std::cout << "Matching " << query.size() << " query entries against " << data.size() << " database entries..." << std::endl;
    auto exact_matches = Blastn::match_filter(query_dustfiltered, data_prepared);
    //std::cout << Blastn::str(exact_matches);

    std::cout << "Pairing " << exact_matches.size() << " words with each other..." << std::endl;
    auto adjacent_pairs = Blastn::pair_filter(exact_matches, query);
    //std::cout << Blastn::str(adjacent_pairs);

    std::cout << "Extending " << adjacent_pairs.size() << " pairs..." << std::endl;
    auto extended_pairs = Blastn::extend_filter(adjacent_pairs, query, data, Blastn::SwMinscore, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);
    //std::cout << Blastn::str(extended_pairs);

    std::cout << "Sorting " << extended_pairs.size() << " extended pairs..." << std::endl;
    auto sorted_epairs = Blastn::sort_filter(extended_pairs, query, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);
    //std::cout << Blastn::str(sorted_epairs);

    std::cout << std::endl;

    /**
     * Blastn finished, write to file
     */

    std::cout << "Writing to file " << Blastn::Output << "..." << std::endl;
    std::ofstream output_file{ Blastn::Output };
    output_file << Blastn::str(sorted_epairs);

    std::cout << std::endl;

    /**
     * Timer stats
     */

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<f32> elapsed = finish - start;
    std::cout << "Done! In " << elapsed.count() << "s." << std::endl;
}

int main(int argc, char **argv)
{
    // arg output
    std::string a;

    // input files
    a = argparse(argc, argv, "-q");
    if (a != Blastn::Invalid) Blastn::QueryFile         = a;
    a = argparse(argc, argv, "-db");
    if (a != Blastn::Invalid) Blastn::DataFile          = a;

    // optional arguments (have defaults)
    a = argparse(argc, argv, "-sp");
    if (a != Blastn::Invalid) Blastn::Seperator         = (char)a[0];
    a = argparse(argc, argv, "-l");
    if (a != Blastn::Invalid) Blastn::SplitLength       = atoi(a.c_str());
    a = argparse(argc, argv, "-m");
    if (a != Blastn::Invalid) Blastn::SwMinscore        = atoi(a.c_str());
    a = argparse(argc, argv, "-ma");
    if (a != Blastn::Invalid) Blastn::SwMatch           = atoi(a.c_str());
    a = argparse(argc, argv, "-mi");
    if (a != Blastn::Invalid) Blastn::SwMismatch        = atoi(a.c_str());
    a = argparse(argc, argv, "-g");
    if (a != Blastn::Invalid) Blastn::SwGap             = atoi(a.c_str());
    a = argparse(argc, argv, "-dt");
    if (a != Blastn::Invalid) Blastn::DustThreshold     = atof(a.c_str());
    a = argparse(argc, argv, "-dl");
    if (a != Blastn::Invalid) Blastn::DustPatternLength = atoi(a.c_str());
    a = argparse(argc, argv, "-o");
    if (a != Blastn::Invalid) Blastn::Output            = a;

    blastn(Blastn::QueryFile, Blastn::DataFile);
    return 0;
}

#else // TEST == true

#include "util/test.hpp"

int main()
{
    Blastn::Test::dust();
    Blastn::Test::extend();
    Blastn::Test::match();
    Blastn::Test::pairs();
    Blastn::Test::sequence();
    Blastn::Test::smith_waterman();
    Blastn::Test::sort();
    Blastn::Test::split();

    std::cin.get();
    return 0;
}

#endif