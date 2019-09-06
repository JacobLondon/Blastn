#ifndef _BLASTN_DICT_H
#define _BLASTN_DICT_H

#include "vector.h"

typedef struct _node_tab {
    char *key;
    void *value;
    u32 type;
} node;

typedef struct _dict_tab {
    u32 *nodes;
} dict;

#endif // _BLASTN_DICT_H