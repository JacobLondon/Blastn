#ifndef _BLASTN_TYPES_H
#define _BLASTN_TYPES_H

#include <stdint.h>

typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;
typedef float f32;
typedef double f64;

enum iterable_types {
    U32,
    NODE,
    VECTOR,
};

typedef struct _vector_tab {
    void *vec;
    u32 type;
    u32 size;
    u32 end;
} vector;

typedef struct _node_tab {
    char *key;
    void *value;
} node;

typedef struct _map_tab {
    vector *buckets;
    u32 type;       // iterable type enum
    u32 size;       // number of buckets
    u32 capacity;   // number of buckets with items
} map;

#endif // _BLASTN_TYPES_H