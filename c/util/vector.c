#include <stdlib.h>
#include "vector.h"

vec_u32 *vector_u32()
{
    vec_u32 *self = malloc(sizeof(vec_u32));
    self->size = VECTOR_DEFAULT_SIZE;
    self->arr = malloc(VECTOR_DEFAULT_SIZE * sizeof(u32));
    self->end = 0;

    return self;
}

void vector_append(vec_u32 *self, u32 value)
{
    // need to reserve more space?
    if (self->end == self->size) {
        // double the capacity
        vector_reserve(self, self->size * 2);
    }

    self->arr[self->end++] = value;
}

void vector_reserve(vec_u32 *self, u32 size)
{
    self->arr = realloc(self->arr, size * sizeof(u32));
}

void vector_free(vec_u32 *self)
{
    free(self->arr);
    free(self);
}
