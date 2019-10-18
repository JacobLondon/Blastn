#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "memory.h"

Vector vector_init(unsigned int size, unsigned int type)
{
    Vector self = { NULL, 0, size };
    switch (type) {
    case UINT:
        self.memory.unint = uint_alloc(size);
        break;
    case MATCH:
        self.memory.match = match_alloc(size);
        break;
    case ADJACENT_PAIR:
        self.memory.adjacent_pair = adjacent_pair_alloc(size);
        break;
    case EXTENDED:
        self.memory.extended = extended_alloc(size);
        break;
    case SORTED:
        self.memory.sorted = sorted_alloc(size);
        break;
    default:
        fprintf(stderr, "Vector init error: Unrecognized type '%d'\n", type);
        exit(-1);
    }

    return self;
}

void vector_delete(Vector self, unsigned int type)
{
    switch (type) {
    case UINT:
        for (unsigned int i = 0; i < self.end; i++)
            self.memory.unint[i] = 0;
        break;
    case MATCH:
        for (unsigned int i = 0; i < self.end; i++)
            self.memory.match[i] = MATCH_DEFAULT;
        break;
    case ADJACENT_PAIR:
        for (unsigned int i = 0; i < self.end; i++)
            self.memory.adjacent_pair[i] = ADJACENT_PAIR_DEFAULT;
        break;
    case EXTENDED:
        for (unsigned int i = 0; i < self.end; i++)
            self.memory.extended[i] = EXTENDED_DEFAULT;
        break;
    case SORTED:
        for (unsigned int i = 0; i < self.end; i++)
            self.memory.sorted[i] = SORTED_DEFAULT;
        break;
    default:
        fprintf(stderr, "Vector delete error: Unrecognized type '%d'\n", type);
        exit(-1);
    }
}

void vector_append_uint(Vector self, unsigned int value)
{
    self.memory.unint[self.end++] = value;
}

void vector_append_match(Vector self, Match value)
{
    self.memory.match[self.end++] = value;
}

void vector_append_adjacent_pair(Vector self, AdjacentPair value)
{
    self.memory.adjacent_pair[self.end++] = value;
}

void vector_append_extended(Vector self, Extended value)
{
    self.memory.extended[self.end++] = value;
}

void vector_append_sorted(Vector self, Sorted value)
{
    self.memory.sorted[self.end++] = value;
}
