#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"

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
 * bucket
 */

bucket *bucket_init(node *value)
{
    bucket *self = malloc(sizeof(bucket));
    self->next = NULL;
    self->item = value;

    return self;
}

void bucket_append(bucket *self, node *value)
{
    bucket *b = self;

    // there is only one item in the list
    if (b->next == NULL)
        goto init;

    // traverse the linked list until the last item is hit
    while (b->next != NULL) {
        b = b->next;
    }

init:
    b->next = bucket_init(value);
}

/**
 * USAGE: Frees itself and returns a pointer to next
 */
bucket *bucket_free(bucket *self)
{
    bucket *b;
    b = self->next;
    node_free(self->item);
    free(self);
    return b;
}

void bucket_print(bucket *self)
{
    if (self == NULL)
        return;
    
    node_print(self->item);
    bucket_print(self->next);
}

/**
 * map
 */

map *map_init(u32 type)
{
    map *self = malloc(sizeof(map));
    self->buckets = malloc(MAP_DEFAULT_SIZE * sizeof(bucket *));
    for (int i = 0; i < MAP_DEFAULT_SIZE; i++) {
        self->buckets[i] = NULL;
    }
    self->type = type;
    self->size = MAP_DEFAULT_SIZE;
    self->capacity = 0;

    return self;
}

void map_insert(map *self, node *n)
{
    u64 index = fnv1a(n->key, self->size);
    bucket *b = self->buckets[index];
    // the bucket hasn't been created yet
    if (b == NULL) {
        self->buckets[index] = bucket_init(n);
    }
    // collision
    else {
        bucket_append(self->buckets[index], n);
    }

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
    bucket *b = self->buckets[index];

    // while keys are not equal
    while (strcmp(b->item->key, key) != 0) {
        // next has a value
        if (b->next != NULL) {
            b = b->next;
        }
        // there is no next item, key not found
        else {
            return NULL;
        }
    }
    // found the bucket
    return b->item;
}

void map_resize(map *self, u32 size)
{
    // temporarily hold the nodes
    node **temp = malloc(self->capacity * sizeof(node *));
    bucket *b;
    u32 i, j;

    // fill temp
    for (i = 0, j = 0; i < self->size; i++) {
        // no bucket at the index
        if (self->buckets[i] == NULL)
            continue;

        // bucket's item into temp
        do {
            // hold the current bucket
            b = self->buckets[i];

            // record the bucket's item into temp
            temp[j++] = b->item;

            // go to the next bucket
            self->buckets[i] = self->buckets[i]->next;

            // free the bucket, item stays in temp
            free(b);
        } while (self->buckets[i] != NULL);
    }

    // reallocate the buckets
    self->buckets = realloc(self->buckets, size * sizeof(bucket));
    self->size = size;

    // fill with NULL
    for (i = 0; i < self->size; i++) {
        self->buckets[i] = NULL;
    }

    // fill self from temp
    for (i = 0; i < self->capacity; i++) {
        // correct for capacity
        self->capacity--;
        map_insert(self, temp[i]);
    }
    // no longer record node pointers
    free(temp);
}

void map_del(map *self, char *key)
{
    u64 index = fnv1a(key, self->size);
    bucket *b = self->buckets[index];
    bucket *prev = NULL;

    // while keys are not equal
    while (strcmp(b->item->key, key) != 0) {
        // next has a value
        if (b->next != NULL) {
            prev = b;
            b = b->next;
        }
        // there is no next item, key not found
        else {
            return;
        }
    }

    // previous was never assigned
    if (prev == NULL) {
        // bucket was the first item found
        self->buckets[index] = bucket_free(b);
    }
    // previous was assigned, bucket is nested
    else {
        // change prev's next to b's next
        prev->next = bucket_free(b);
    }
}

void map_free(map *self)
{
    bucket *b;

    // free all the buckets
    for (u32 i = 0; i < self->size; i++) {
        // no bucket at the index
        if (self->buckets[i] == NULL)
            continue;
        
        // a bucket must have been found
        b = self->buckets[i];
        // free everything in the bucket
        do {
            b = bucket_free(b);
        } while (b->next != NULL);
    }

    // free self
    free(self->buckets);
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
