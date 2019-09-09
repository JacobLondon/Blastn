#ifndef _BLASTN_VECTOR_H
#define _BLASTN_VECTOR_H

#include "types.h"

// default number of items to reserve space for
#define VECTOR_DEFAULT_SIZE 8

#define vector_begin(vecid) triplets.vec
#define vector_end(type, vecid) &(pointer_of(type, vecid.vec)[vecid.size - 1])

vector *vector_init(u32 type, u32 size);
void vector_append(vector *self, void *value);
void vector_reserve(vector *self, u32 size);
void vector_free(vector *self);

#endif // _BLASTN_VECTOR_H