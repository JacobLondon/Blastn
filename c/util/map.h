#ifndef _BLASTN_MAP_H
#define _BLASTN_MAP_H

#include "types.h"

/**
 * node
 */

typedef struct _node_tab {
    char *key;
    void *value;
} node;

node *node_init(char *key, void *value);
void node_free(node *self);
void node_print(node *self);

/**
 * bucket
 */

typedef struct _bucket_tab {
    struct _bucket_tab *next;
    node *item;
} bucket;

bucket *bucket_init(node *value);
void bucket_append(bucket *self, node *value);
bucket *bucket_free(bucket *self);
void bucket_print(bucket *self);

/**
 * map
 */

#define MAP_DEFAULT_SIZE 8      /* must be power of 2 */
#define MAP_RESIZE_RATIO 0.67

typedef struct _map_tab {
    bucket **buckets;
    u32 type;       // iterable type enum
    u32 size;       // number of buckets
    u32 capacity;   // number of buckets with items
} map;

map *map_init(u32 type);
node *map_at(map *self, char *key);
void map_insert(map *self, node *n);
void map_resize(map *self, u32 size);
void map_del(map *self, char *key);
void map_free(map *self);

/**
 * hash
 */

u64 fnv1a(const char *text, u32 bytes);

#endif // _BLASTN_MAP_H