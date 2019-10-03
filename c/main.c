#define TEST true

#if TEST == false

#include <string.h>
#include <stdlib.h>
#include "util/globals.h"
#include "lib/blastn.h"
#include "tools/vector.h"

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

static void blastn(char *query_file, char *data_file)
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

int main(int argc, char **argv)
{
    char *a = calloc(BlastnMaxWidth, sizeof(char));
    char *query_file = calloc(BlastnMaxWidth, sizeof(char));
    char *data_file = calloc(BlastnMaxWidth, sizeof(char));

    // required arguments (no defaults)
    strcpy(query_file, argparse(argc, argv, "-q"));
    if (strcmp(query_file, BlastnInvalid) == 0) {
        fprintf(stderr, "Failure: Invalid query file: %s\n", query_file);
        exit(-1);
    }
    strcpy(data_file, argparse(argc, argv, "-db"));
    if (strcmp(query_file, BlastnInvalid) == 0) {
        fprintf(stderr, "Failure: Invalid data file: %s\n", data_file);
        exit(-1);
    }

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

    blastn(query_file, data_file);
    return 0;
}

#else

#include "util/test.h"

int main()
{
    init_globals();
    tsplit();
    //tsmith_waterman();
    //tsequence();
    //tmatch();
    //tdust();
    //textend();

    gets();
    return 0;
}

#endif