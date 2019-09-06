#ifndef _BLASTN_TYPES_H
#define _BLASTN_TYPES_H

#include <stdint.h>

typedef uint32_t u32;
typedef int32_t s32;
typedef float f32;
typedef double f64;

enum iterable_types {
    U32,
    DICT,
    NODE,
};

#endif // _BLASTN_TYPES_H