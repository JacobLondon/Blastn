#include <stdlib.h>
#include "vector.h"

vector *vector_init(u32 type)
{
    vector *self = malloc(sizeof(vector));
    self->type = type;
    // reserve based on type
    switch (self->type) {
    case U32:
        self->buf = malloc(VECTOR_DEFAULT_SIZE * sizeof(u32));
        break;
    }
    self->size = VECTOR_DEFAULT_SIZE;
    self->end = 0;

    return self;
}

void vector_append(vector *self, void *value)
{
    // need to reserve more space?
    if (self->end == self->size) {
        // double the capacity
        vector_reserve(self, self->size * 2);
    }

    // set the value based on type
    switch (self->type) {
    case U32:
        ((u32 *)self->buf)[self->end++] = *((u32 *)value);
        break;
    }
}

void vector_reserve(vector *self, u32 size)
{
    // reserve based on type
    switch (self->type) {
    case U32:
        self->buf = realloc(self->buf, size * sizeof(u32));
        break;
    }
}

void vector_free(vector *self)
{
    free(self->buf);
    free(self);
}
