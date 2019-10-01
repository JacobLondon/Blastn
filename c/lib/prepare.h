#ifndef BLASTN_PREPARE_H
#define BLASTN_PREPARE_H

#include "../tools/types.h"

sequence_map *build_sequence(char *path, char sep);

indexed_sequence_map *split_sequence(sequence_map *data, u32 length);

indexed_sequence_map *prepare_sequence(char *path, u32 length, char sep);

#endif // BLASTN_PREPARE_H