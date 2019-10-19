#include <string.h>
#include <stdio.h>
#include "util/util.h"
#include "lib/blastn.h"

int main(int argc, char **argv)
{
    int test = strfind("-test", argv, argc);

    if (!test)
        blastn(argc, argv);
    else
        blastn_test(argc, argv);

    #ifdef _WIN32
        puts("\nBlastn has completed. Press ENTER to exit...");
        gets();
    #endif

    return 0;
}
