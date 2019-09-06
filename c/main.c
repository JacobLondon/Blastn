#include <stdio.h>
#include "util/vector.h"

int main()
{
    vec *myvec = vector(U32);
    for (int i = 0; i < 12; i++) {
        vector_append(myvec, &i);
    }
    for (int i = 0; i < myvec->end; i++) {
        printf("%d\n", ((u32 *)myvec->buf)[i]);
    }

    return 0;
}