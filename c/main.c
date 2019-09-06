#include <stdio.h>
#include "util/map.h"

int main()
{
    map *m = map_init(U32);
    u32 a = 'a';
    u32 b = 'b';
    u32 c = 'b';
    u32 d = 'c';
    map_insert(m, node_init("test", (void *)&a));
    map_insert(m, node_init("different", (void *)&b));
    map_insert(m, node_init("ldq", (void *)&c));

    for (int i = 0; i < m->size; i++) {
        if (m->buckets[i] == NULL)
            printf("NULL\n");
        else
            bucket_print(m->buckets[i]);
    }

    return 0;
}