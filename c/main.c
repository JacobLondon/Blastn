#define TEST true

#if TEST == false

#include <string.h>
#include "util/globals.h"
#include "lib/blastn.h"
#include "tools/vector.h"
#include "tools/string.h"

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
    //sequence_map query = build_sequence
}

int main()
{
    init_globals();
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