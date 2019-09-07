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
    self->key = key;
    self->value = value;
    
    return self;
}

void node_free(node *self)
{
    free(self->key);
    free(self->value);
    free(self);
}

void node_print(node *self)
{
    printf("(%s, %d)\n", self->key, *((u32 *)self->value));
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
        ((vector **)self->buckets->vec)[i] = NULL;
    

    return self;
}

void map_insert(map *self, node *n)
{
    u64 index = fnv1a(n->key, self->size);

    // the bucket hasn't been created yet
    if (((vector **)self->buckets->vec)[index] == NULL)
        ((vector **)self->buckets->vec)[index] = vector_init(NODE, 1);
    // collision
    else
        vector_append(((vector **)self->buckets->vec)[index], n);
    
    // track the inserted item
    self->capacity++;

    // check the capacity to size ratio
    if (self->capacity >= self->size * MAP_RESIZE_RATIO) {
        printf("Resize, %d >= %f\n", self->capacity, self->size * MAP_RESIZE_RATIO);
        // double the size when the ratio is surpassed
        map_resize(self, self->size * 2);
    }
}

node *map_at(map *self, char *key)
{
    u64 index = fnv1a(key, self->size);
    // the bucket the key is in
    vector *bkt = &self->buckets[index];

    // look for the key in the bucket vector
    for (u32 i = 0; i < bkt->size; i++) {
        if (strcmp(((node **)bkt->vec)[i]->key, key))
            return ((node **)bkt->vec)[i];
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
    for (i = 0; i < self->size; i++) {
        // the bucket is empty
        if (((vector **)self->buckets->vec)[i] == NULL)
            continue;

        // traverse the bucket, record nodes
        for (j = 0; j < ((vector **)self->buckets)[i]->size; j++)
            vector_append(temp, ((vector **)self->buckets->vec)[i]);
        
        // free the bucket, nodes stay in temp
        vector_free(((vector **)self->buckets->vec)[i]);
    }

    // reallocate the buckets
    vector_reserve(self->buckets, size);
    self->size = size;

    // fill with NULL
    for (i = 0; i < self->size; i++)
        ((vector **)self->buckets->vec)[i] = NULL;

    // fill self from temp
    for (i = 0; i < temp->size; i++) {
        // correct for capacity++ in insert
        self->capacity--;
        map_insert(self, ((node **)temp->vec)[i]);
    }

    vector_free(temp);
}

void map_free(map *self)
{
    // traverse the map
    for (u32 i = 0; i < self->size; i++) {
        // the bucket is empty
        if (((vector **)self->buckets->vec)[i] == NULL)
            continue;
        // traverse the bucket, free every node
        for (u32 j = 0; j < ((vector **)self->buckets)[i]->size; j++) {
            // array pointer of array pointers of node pointer to node pointers
            node_free(((node **)((vector **)self->buckets->vec)[i]->vec)[j]);
        }
        // free each bucket
        vector_free(((vector **)self->buckets->vec)[i]);
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

u64 fnv1a(const char *text, u32 bytes)
{
    u64 hash = Seed;
    while (*text)
        hash = (*text++ ^ hash) * Prime;
    hash = (hash >> (64 - (bytes >> 2)));
    //printf("Hash: %ld\n", hash);
    return hash;
}
