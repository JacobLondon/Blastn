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
				std::cout << "Failure: Invalid argument usage: " << arg << std::endl;
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
	std::cout << "Formatting..." << std::endl;
	auto query = build_sequence(query_file, Blastn::Seperator);
	auto data = build_sequence(data_file, Blastn::Seperator);
	auto query_prepared = split_sequence(query, Blastn::SplitLength);
	auto data_prepared = split_sequence(data, Blastn::SplitLength);

	std::cout << "Smith Waterman..." << std::endl;
	auto query_swfiltered = smith_waterman_filter(query_prepared, Blastn::SwMinscore, Blastn::SwMatch, Blastn::SwMismatch, Blastn::SwGap);
	//Blastn::print(query_swfiltered);

	std::cout << "Dust..." << std::endl;
	auto query_dustfiltered = dust_filter(query_swfiltered, Blastn::DustThreshold, Blastn::DustPatternLength, Blastn::SplitLength);
	//Blastn::print(query_dustfiltered);

	std::cout << "Exact matches..." << std::endl;
	auto exact_matches = match_filter(query_dustfiltered, data_prepared);
	//auto exact_matches = match_filter(query_swfiltered, data_prepared);

	// adjacent_pairs

	// extended_pairs

	// sorted_epairs

	std::cout << "Printing output..." << std::endl;
	Blastn::print(exact_matches);

	std::cout << "...Done" << std::endl;
}

int main(int argc, char **argv)
{
	std::string a;
	std::string query_file;
	std::string data_file;

	// required arguments (no defaults)
	query_file = argparse(argc, argv, "-q");
	if (query_file == Blastn::Invalid) {
		std::cout << "Failure: Invalid query file: " << query_file << std::endl;
		exit(-1);
	}
	data_file = argparse(argc, argv, "-db");
	if (data_file == Blastn::Invalid) {
		std::cout << "Failure: Invalid data file: " << data_file << std::endl;
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
