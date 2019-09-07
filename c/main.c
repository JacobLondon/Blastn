#include <stdio.h>
#include <stdlib.h>
#include "util/map.h"

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

int main()
{
    map *m = map_init(U32);
    u32 a = 'a';
    for (int i = 0; i < 22; i++) {
        char *test = malloc(sizeof(char) * 10);
        printf("%d\n", i);
        map_insert(m, node_init(rand_string(test, 10), (void *)&a));
    }

    // traverse the map
    for (u32 i = 0; i < m->size; i++) {
        // the bucket is empty
        if (((vector **)m->buckets->vec)[i] == NULL) {
            printf("NULL\n");
            continue;
        }
        // traverse the bucket, free every node
        for (u32 j = 0; j < ((vector **)m->buckets)[i]->size; j++) {
            // array pointer of array pointers of node pointer to node pointers
            node_print(((node **)((vector **)m->buckets->vec)[i]->vec)[j]);
        }
    }

    return 0;
}