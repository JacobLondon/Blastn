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

map *map_init(u32 type);
node *map_at(map *self, char *key);
void map_insert(map *self, node *n);
void map_resize(map *self, u32 size);
void map_free(map *self);

/**
 * hash
 */

u64 fnv1a(const char *text, u32 bytes);

#endif // _BLASTN_MAP_H