#ifndef BLASTN_PREPARE_H
#define BLASTN_PREPARE_H

#include "../util/types.h"

SequenceMap *build_sequence(char *path, char sep);

IndexedSequenceMap *split_sequence(SequenceMap *data, unsigned int length);

IndexedSequenceMap *prepare_sequence(char *path, unsigned int length, char sep);

#endif // BLASTN_PREPARE_H