#ifndef _BLASTN_VECTOR_H
#define _BLASTN_VECTOR_H

#include "types.h"

// default number of items to reserve space for
#define VECTOR_DEFAULT_SIZE 8

typedef struct _vector_tab {
    void *buf;
    u32 type;
    u32 size;
    u32 end;
} vec;

vec *vector(u32 type);
void vector_append(vec *self, void *value);
void vector_reserve(vec *self, u32 size);
void vector_free(vec *self);

#endif // _BLASTN_VECTOR_H