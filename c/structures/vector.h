#ifndef BLASTN_VECTOR_H
#define BLASTN_VECTOR_H

#include "types.h"

Vector vector_init(unsigned int size, unsigned int type);
void vector_delete(Vector self, unsigned int type);
void vector_append_uint(Vector self, unsigned int value);
void vector_append_match(Vector self, Match value);
void vector_append_adjacent_pair(Vector self, AdjacentPair value);
void vector_append_extended(Vector self, Extended value);
void vector_append_sorted(Vector self, Sorted value);

#endif // BLASTN_VECTOR_H