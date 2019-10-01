#define TEST true

#if TEST == false

#include "util/globals.h"
#include "lib/blastn.h"

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