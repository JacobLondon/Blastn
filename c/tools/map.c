#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"
#include "vector.h"

/**
 * node
 */

node *node_init(char *key, void *value)
{
    node *self = malloc(sizeof(node));
    self->key = malloc((1 + strlen(key)) * sizeof(char));
    strcpy(self->key, key);
    self->value = value;
    
    return self;
}

void node_free(node *self)
{
    if (self != NULL) {
        free(self->key);
        free(self);
    }
}

void node_print(node *self)
{
    printf("(%s, %d)\n", self->key, ref(u32, self->value));
}

/**
 * map
 */

map *map_init(u32 type)
{
    map *self = malloc(sizeof(map));

    self->size = MAP_DEFAULT_SIZE;
    self->capacity = 0;
    self->type = type;
    self->buckets = vector_init(NODE, MAP_DEFAULT_SIZE);

    // vector to track an array of vector pointers
    for (int i = 0; i < MAP_DEFAULT_SIZE; i++)
        bucket_at(self, i) = NULL;

    return self;
}

void map_insert(map *self, node *n)
{
    u64 index = fnv1a(n->key, self->size);

    // the bucket hasn't been created yet
    if (bucket_at(self, index) == NULL)
        bucket_at(self, index) = vector_init(NODE, 1);
    
    // check if the key is in the bucket
    for (u32 i = 0; i < bucket_at(self, index)->end; i++) {
        // the key exists, replace it with the new node and exit
        if (strcmp(n->key, node_at(self, index, i)->key) == 0) {
            node_free(node_at(self, index, i));
            node_at(self, index, i) = n;
            return;
        }
    }

    // append the node, a bucket must be there
    vector_append(bucket_at(self, index), n);
    
    // track the inserted item
    self->capacity++;

    // check the capacity to size ratio
    if (self->capacity >= self->size * MAP_RESIZE_RATIO) {
        // double the size when the ratio is surpassed
        map_resize(self, self->size * 2);
    }
}

node *map_at(map *self, char *key)
{
    u64 index = fnv1a(key, self->size);
    // the bucket the key is in
    vector *bkt = bucket_at(self, index);

    // look for the key in the bucket vector
    for (u32 i = 0; i < bucket_at(self, index)->end; i++) {
        if (bucket_at(self, index) == NULL)
            continue;
        if (strcmp(node_at(self, index, i)->key, key) == 0)
            return node_at(self, index, i);
    }

    // key not found
    return NULL;
}

void map_resize(map *self, u32 size)
{
    // temporarily hold the nodes
    vector *temp = vector_init(NODE, self->capacity);
    //bucket *b;
    u32 i, j;

    // traverse the map
    for (i = 0; i < self->buckets->size; i++) {
        // the bucket is empty
        if (bucket_at(self, i) == NULL)
            continue;

        // traverse the bucket, record nodes
        for (j = 0; j < bucket_at(self, i)->end; j++) {
            vector_append(temp, node_at(self, i, j));
        }
        
        // free the bucket, nodes stay in temp
        vector_free(bucket_at(self, i));
    }

    // reallocate the buckets
    vector_reserve(self->buckets, size);
    self->size = size;

    // fill with NULL
    for (i = 0; i < self->size; i++)
        bucket_at(self, i) = NULL;

    // fill self from temp
    for (i = 0; i < temp->end; i++) {
        // correct for capacity++ in insert
        self->capacity--;
        map_insert(self, ((node **)temp->vec)[i]);
    }

    vector_free(temp);
}

void map_free(map *self)
{
    if (self == NULL)
        return;

    // traverse the map
    for (u32 i = 0; i < self->size; i++) {
        // the bucket is empty
        if (bucket_at(self, i) == NULL)
            continue;
        // traverse the bucket, free every node
        for (u32 j = 0; j < bucket_at(self, i)->end; j++) {
            node_free(node_at(self, i, j));
        }
        // free each bucket
        vector_free(bucket_at(self, i));
    }
    // free the map array and the map
    vector_free(self->buckets);
    free(self);
}

/**
 * hash
 */

// https://create.stephan-brumme.com/fnv-hash/
const u64 Prime = 0x01000193; //   16777619
const u64 Seed  = 0x811C9DC5; // 2166136261

/**
 * @max MUST BE A POWER OF 2
 */
u64 fnv1a(const char *text, u32 max)
{
    u64 hash = Seed;
    while (*text)
        hash = (*text++ ^ hash) * Prime;
    
    // 64 bit number into the range defined by max
    hash = hash % max;
    //printf("Hash: %ld\n", hash);
    return hash;
}

/**
 * test
 */

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";
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

static map_test()
//void main()
{
    map *m = map_init(I32);
    u32 a = 'a';

    map_insert(m, node_init("aaaa", pointer_to(a)));
    map_insert(m, node_init("aa2a", pointer_to(a)));
    map_insert(m, node_init("aa12a", pointer_to(a)));
    map_insert(m, node_init("aaaa", pointer_to(a)));
    map_insert(m, node_init("a43aaa", pointer_to(a)));
    map_insert(m, node_init("aaaa", pointer_to(a)));
    map_insert(m, node_init("aafasdaa", pointer_to(a)));
    map_insert(m, node_init("aaaa", pointer_to(a)));
    map_insert(m, node_init("aaadsaa", pointer_to(a)));
    map_insert(m, node_init("afaaa", pointer_to(a)));
    map_insert(m, node_init("adaadaaa", pointer_to(a)));

    printf("capacity: %d\nsize: %d\n", m->capacity, m->size);

    node *n;
    map_for_each(m, n) {
        printf("Bucket %d:", __b);
        node_print(n);
    }

    printf("aaaa: ");
    printf("%d\n", ref(u32, map_at(m, "aaaa")->value));

    map_free(m);
}
