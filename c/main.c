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
        map_insert(m, node_init(rand_string(test, 10), (void *)&a));
    }

    for (int i = 0; i < m->size; i++) {
        if (m->buckets[i] == NULL)
            printf("NULL\n");
        else {
            printf("Bucket:\n");
            bucket_print(m->buckets[i]);
        }
    }

    return 0;
}