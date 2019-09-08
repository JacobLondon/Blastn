#ifndef _BLASTN_MAP_H
#define _BLASTN_MAP_H

#include "types.h"

/**
 * node
 */

node *node_init(char *key, void *value);
void node_free(node *self);
void node_print(node *self);

/**
 * map
 */

#define MAP_DEFAULT_SIZE 8      /* must be power of 2 */
#define MAP_RESIZE_RATIO 0.67f

#define node_at(mapid, bindex, nindex) \
    ((node **)bucket_at((mapid), (bindex))->vec)[(nindex)]

#define bucket_at(mapid, index) \
    ((vector **)(mapid)->buckets->vec)[(index)]

#define map_for_each(mapid, nodep) \
    for (u32 __b = 0; __b < (mapid)->size; __b++) \
        if (bucket_at((mapid), __b) == NULL) \
            continue; \
        else \
            for (u32 __n = 0; __n < bucket_at((mapid), __b)->end; __n++) \
                if ((nodep = node_at((mapid), __b, __n)) != NULL)
        

map *map_init(u32 type);
node *map_at(map *self, char *key);
void map_insert(map *self, node *n);
void map_resize(map *self, u32 size);
void map_free(map *self);

/**
 * hash
 */

u64 fnv1a(const char *text, u32 max);

#endif // _BLASTN_MAP_H