#ifndef _BLASTN_VECTOR_H
#define _BLASTN_VECTOR_H

#include "types.h"

// default number of items to reserve space for
#define VECTOR_DEFAULT_SIZE 8

typedef struct _vector_u32_tab {
    u32 *arr;
    u32 size;
    u32 end;
} vec_u32;

vec_u32 *vector_u32();
void vector_append(vec_u32 *self, u32 value);
void vector_reserve(vec_u32 *self, u32 size);
void vector_free(vec_u32 *self);

#endif // _BLASTN_VECTOR_H