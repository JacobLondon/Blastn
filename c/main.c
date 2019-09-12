#define TEST true

#if TEST == false

#include "util/globals.h"
#include "lib/blastn.h"

int main()
{

    return 0;
}

#else

#include "util/test.h"

int main()
{
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