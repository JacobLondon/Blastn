#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

vector *vector_init(u32 type, u32 size)
{
    vector *self = malloc(sizeof(vector));
    self->type = type;
    // reserve based on type
    switch (self->type) {
    case I32:
        self->vec = calloc(size, sizeof(u32));
        break;
    case STRING:
        self->vec = calloc(size, sizeof(string *));
        break;
    case NODE:
        self->vec = calloc(size, sizeof(node *));
        break;
    case VECTOR:
        self->vec = calloc(size, sizeof(vector *));
        break;
    case MAP:
        self->vec = calloc(size, sizeof(map *));
        break;
    }
    self->size = size;
    self->end = 0;

    return self;
}

void vector_append(vector *self, void *value)
{
    // need to reserve more space?
    if (self == NULL)
        printf("NULL\n");
    if (self->end == self->size) {
        // double the capacity
        vector_reserve(self, self->size * 2);
    }

    // set the value based on type
    switch (self->type) {
    case I32:
        ((u32 *)self->vec)[self->end++] = *((u32 *)value);
        break;
    case STRING:
        ((string **)self->vec)[self->end++] = (string *)value;
        break;
    case NODE:
        ((node **)self->vec)[self->end++] = (node *)value;
        break;
    case VECTOR:
        ((vector **)self->vec)[self->end++] = (vector *)value;
        break;
    case MAP:
        ((map **)self->vec)[self->end++] = (map *)value;
        break;
    }
}

void vector_reserve(vector *self, u32 size)
{
    // reserve based on type
    switch (self->type) {
    case I32:
        self->vec = realloc(self->vec, size * sizeof(u32));
        break;
    case STRING:
        self->vec = realloc(self->vec, size * sizeof(string *));
        break;
    case NODE:
        self->vec = realloc(self->vec, size * sizeof(node *));
        break;
    case VECTOR:
        self->vec = realloc(self->vec, size * sizeof(vector *));
        break;
    case MAP:
        self->vec = realloc(self->vec, size * sizeof(map *));
        break;
    }
    self->size = size;
}

void vector_free(vector *self)
{
    if (self == NULL)
        return;

    if (self->vec != NULL)
        free(self->vec);
    
    free(self);
}
