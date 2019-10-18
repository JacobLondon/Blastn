#ifndef BLASTN_MEMORY_H
#define BLASTN_MEMORY_H

#include "types.h"

#define UINT_MEM_SIZE          0xFFFFFF
#define MATCH_MEM_SIZE         10000
#define ADJACENT_PAIR_MEM_SIZE 100
#define EXTENDED_MEM_SIZE      100
#define SORTED_MEM_SIZE        100

extern unsigned int vector_uint_memory[];
unsigned int *uint_alloc(unsigned int size);
#define VECTOR_UINT_DEFAULT { vector_uint_memory, 0, 0 }

extern Match vector_match_memory[];
Match *match_alloc(unsigned int size);
#define VECTOR_MATCH_DEFAULT { vector_match_memory, 0, 0 }

extern AdjacentPair vector_adjacent_pair_memory[];
AdjacentPair *adjacent_pair_alloc(unsigned int size);
#define VECTOR_ADJACENT_PAIR_DEFAULT { vector_adjacent_pair_memory, 0, 0 }

extern Extended vector_extended_memory[];
Extended *extended_alloc(unsigned int size);
#define VECTOR_EXTENDED_DEFAULT { vector_extended_memory, 0, 0}

extern Sorted vector_sorted_memory[];
Sorted *sorted_alloc(unsigned int size);
#define VECTOR_SORTED_DEFAULT { vector_sorted_memory, 0, 0 }

#define MATCH_DEFAULT (Match){ NULL, VECTOR_UINT_DEFAULT, VECTOR_UINT_DEFAULT }
#define ADJACENT_PAIR_DEFAULT (AdjacentPair){ NULL, NULL, 0, 0, 0, 0, 0 }
#define EXTENDED_DEFAULT (Extended){ NULL, 0, 0 }
#define SORTED_DEFAULT (Sorted){ NULL, 0, 0 }

#endif // BLASTN_MEMORY_H