#include <stdlib.h>
#include "vector.h"
#include "dict.h"

vec *vector(u32 type)
{
    vec *self = malloc(sizeof(vec));
    self->type = type;
    // reserve based on type
    switch (self->type) {
    case U32:
        self->buf = malloc(VECTOR_DEFAULT_SIZE * sizeof(u32));
        break;
    case DICT:
        self->buf = malloc(VECTOR_DEFAULT_SIZE * sizeof(dict));
        break;
    case NODE:
        self->buf = malloc(VECTOR_DEFAULT_SIZE * sizeof(node));
        break;
    }
    self->size = VECTOR_DEFAULT_SIZE;

    self->end = 0;

    return self;
}

void vector_append(vec *self, void *value)
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
    case DICT:
        ((dict *)self->buf)[self->end++] = *((dict *)value);
        break;
    case NODE:
        ((node *)self->buf)[self->end++] = *((node *)value);
        break;
    }
}

void vector_reserve(vec *self, u32 size)
{
    // reserve based on type
    switch (self->type) {
    case U32:
        self->buf = realloc(self->buf, size * sizeof(u32));
        break;
    case DICT:
        self->buf = realloc(self->buf, size * sizeof(dict));
        break;
    case NODE:
        self->buf = realloc(self->buf, size * sizeof(node));
        break;
    }
}

void vector_free(vec *self)
{
    free(self->buf);
    free(self);
}
