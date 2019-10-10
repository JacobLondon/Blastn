#define TEST false

#if TEST == false

#include "util/globals.hpp"
#include "lib/blastn.hpp"

static std::string argparse(int argc, char **argv, std::string arg)
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
    for (int i = 0; i < arguments.size(); i++) {
        if (arg == arguments[i]) {
            if (i + 1 >= arguments.size()) {
                std::fprintf(stderr, "Failure: Invalid argument usage: %s\n", arg);
                exit(-1);
            }
            else
                return arguments[i + 1];
        }
    }
    return Blastn::Invalid;
}

static void blastn(std::string query_file, std::string data_file)
{
    std::printf("Formatting...\n");
    auto query = build_sequence(query_file, Blastn::Seperator);
    auto data = build_sequence(data_file, Blastn::Seperator);
    auto query_prepared = split_sequence(query, Blastn::SplitLength);
    auto data_prepared = split_sequence(data, Blastn::SplitLength);

    std::printf("Smith Waterman...\n");
    auto query_swfiltered = smith_waterman_filter(query_prepared, Blastn::SwMinscore, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);
    //Blastn::print(query_swfiltered);

    std::printf("Dust...\n");
    auto query_dustfiltered = dust_filter(query_swfiltered, Blastn::DustThreshold, Blastn::DustPatternLength, Blastn::SplitLength);
    //Blastn::print(query_dustfiltered);

    std::printf("Exact Matches...\n");
    auto exact_matches = match_filter(query_dustfiltered, data_prepared);
    //auto exact_matches = match_filter(query_swfiltered, data_prepared);

    std::printf("Adjacent Pairs...\n");
    auto adjacent_pairs = pair_filter(exact_matches, query);

    std::printf("Extended Pairs...\n");
    auto extended_pairs = extend_filter(adjacent_pairs, query, data, Blastn::SwMinscore, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);

    std::printf("Sorted, Extended Pairs...\n");
    auto sorted_epairs = sort_filter(extended_pairs, query, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);

    std::printf("Printing output...\n");
    Blastn::print(sorted_epairs);

    std::printf("...Done\n");
}

int main(int argc, char **argv)
{
    std::string a;
    std::string query_file;
    std::string data_file;

    // required arguments (no defaults)
    query_file = argparse(argc, argv, "-q");
    if (query_file == Blastn::Invalid) {
        std::fprintf(stderr, "Failure: Invalid query file: %s\n", query_file);
        exit(-1);
    }
    data_file = argparse(argc, argv, "-db");
    if (data_file == Blastn::Invalid) {
        std::fprintf(stderr, "Failure: Invalid data file: %s\n", data_file);
        exit(-1);
    }

    // optional arguments (have defaults)
    a = argparse(argc, argv, "-sp");
    if (a != Blastn::Invalid) Blastn::Seperator = (char)a[0];
    a = argparse(argc, argv, "-l");
    if (a != Blastn::Invalid) Blastn::SplitLength = atoi(a.c_str());
    a = argparse(argc, argv, "-m");
    if (a != Blastn::Invalid) Blastn::SwMinscore = atoi(a.c_str());
    a = argparse(argc, argv, "-ma");
    if (a != Blastn::Invalid) Blastn::SwMatch = atoi(a.c_str());
    a = argparse(argc, argv, "-mi");
    if (a != Blastn::Invalid) Blastn::SwMismatch = atoi(a.c_str());
    a = argparse(argc, argv, "-g");
    if (a != Blastn::Invalid) Blastn::SwGap = atoi(a.c_str());
    a = argparse(argc, argv, "-dt");
    if (a != Blastn::Invalid) Blastn::DustThreshold = atof(a.c_str());
    a = argparse(argc, argv, "-dl");
    if (a != Blastn::Invalid) Blastn::DustPatternLength = atoi(a.c_str());
    a = argparse(argc, argv, "-o");
    if (a != Blastn::Invalid) Blastn::Output = a;

    blastn(query_file, data_file);
    return 0;
}

#else

#include "util/test.hpp"
int main(int argc, char** argv)
{
    //tsplit();
    //tsmith_waterman();
    //tsequence();
    //tmatch();
    //tdust();
    textend();

    std::cin.get();
    return 0;
}
#endif
