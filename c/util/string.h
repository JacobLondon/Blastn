#ifndef _BLASTN_STRING_H
#define _BLASTN_STRING_H

#include "types.h"

#define STRING_DEFAULT_SIZE 8

typedef struct _string_tab {
    char *c_str;
    u32 size;
} str;

str *string(const char *value);
void string_append(str *self, char *s);
void string_set(str *self, const char *s);
void string_free(str *self);

#endif // _BLASTN_STRING_H