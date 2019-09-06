#include <stdlib.h>
#include <string.h>
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
    bucket *i = self->next;
    while (i != NULL)
        i = i->next;
    
    i->next = bucket_init(value);
}

/**
 * USAGE: Frees itself and returns a pointer to next
 */
bucket *bucket_free(bucket *self)
{
    bucket *b;
    node_free(self->item);
    b = self->next;
    free(self);
    return b;
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

void map_insert(map *self, char *key, void *value)
{
    u64 index = fnv1a(key, self->size);
    bucket *b = self->buckets[index];
    node *n = node_init(key, value);

    // the bucket hasn't been created yet
    if (b == NULL) {
        self->buckets[index] = bucket_init(n);
    }
    // collision
    else {
        bucket_append(self->buckets[index], n);
    }
    self->capacity++;
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

// TODO
void map_resize(map *self, u32 size)
{
    self->buckets = realloc(self->buckets, size * sizeof(bucket));
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

u64 fnv1a(const char *text, u32 bytes)
{
    u64 hash = Seed;
    while (*text)
        hash = (*text++ ^ hash) * Prime;
    return (hash >> (64 - (bytes * 4)));
}
