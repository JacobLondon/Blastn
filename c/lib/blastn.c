#include "blastn.h"
#include "../util/globals.h"
#include "../util/test.h"
#include "../util/display.h"

static char *argparse(int argc, char **argv, char *arg)
{
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], arg) == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Failure: Invalid argument usage: %s\n", arg);
                exit(-1);
            }
            else
                return argv[i + 1];
        }
    }
    return BlastnInvalid;
}

int test(int argc, char **argv)
{
    init_globals();
    char a[BlastnMaxWidth] = {0};

    strcpy(a, argparse(argc, argv, "-test"));
    if (strcmp(a, BlastnInvalid) != 0) {
        fprintf(stderr, "Error: Unknown test function argument.\n");
        exit(-1);
    }

    if (strcmp(a, "dust") == 0)
        test_dust();
    else if (strcmp(a, "extend") == 0)
        test_extend();
    else if (strcmp(a, "match") == 0)
        test_match();
    else if (strcmp(a, "pairs") == 0)
        test_pairs();
    else if (strcmp(a, "sequence") == 0)
        test_sequence();
    else if (strcmp(a, "sw") == 0 || strcmp(a, "smithwaterman") == 0)
        test_smith_waterman();
    else if (strcmp(a, "sort") == 0)
        test_sort();
    else if (strcmp(a, "split") == 0)
        test_split();
    else
        fprintf(stderr, "Unknown test function: %s\n", a);

    return 0;
}

static void align(char *query_file, char *data_file)
{
    printf("Formatting...\n");
    sequence_map *query = build_sequence(query_file, BlastnSeperator);
    sequence_map *data  = build_sequence(data_file, BlastnSeperator);
    indexed_sequence_map *query_prepared = split_sequence(query, BlastnSplitLength);
    indexed_sequence_map *data_prepared  = split_sequence(data, BlastnSplitLength);

    printf("Smith Waterman...\n");
    indexed_sequence_map *query_swfiltered = smith_waterman_filter(query_prepared, BlastnSwMinscore, BlastnSwMatch, BlastnSwMismatch, BlastnSwGap);

    printf("Dust...\n");
    indexed_sequence_map *query_dustfiltered = dust_filter(query_swfiltered, BlastnDustThreshold, BlastnDustPatternLength, BlastnSplitLength);

    printf("Exact Matches...\n");


}

int blastn(int argc, char **argv)
{
    char a[BlastnMaxWidth] = {0};

    // input files
    strcpy(a, argparse(argc, argv, "-q"));
    if (strcmp(a, BlastnInvalid) != 0) strcpy(BlastnQueryFile, a);
    strcpy(a, argparse(argc, argv, "-db"));
    if (strcmp(a, BlastnInvalid) != 0) strcpy(BlastnDataFile, a);

    // optional arguments (have defaults)
    strcpy(a, argparse(argc, argv, "-sp"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnSeperator = (char)a[0];
    strcpy(a, argparse(argc, argv, "-l"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnSplitLength = atoi(a);
    strcpy(a, argparse(argc, argv, "-m"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnSwMinscore = atoi(a);
    strcpy(a, argparse(argc, argv, "-ma"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnSwMatch = atoi(a);
    strcpy(a, argparse(argc, argv, "-mi"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnSwMismatch = atoi(a);
    strcpy(a, argparse(argc, argv, "-g"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnSwGap = atoi(a);
    strcpy(a, argparse(argc, argv, "-dt"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnDustThreshold = atof(a);
    strcpy(a, argparse(argc, argv, "-dl"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnDustPatternLength = atoi(a);
    strcpy(a, argparse(argc, argv, "-sp"));
    if (strcmp(a, BlastnInvalid) != 0) BlastnOutput = a;

    blastn(BlastnQueryFile, BlastnQueryFile);
    return 0;
}
