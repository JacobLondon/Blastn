#ifndef BLASTN_STRING_H
#define BLASTN_STRING_H

#include "types.h"

#define STRING_DEFAULT_SIZE 8

string *string_init(u32 size);
void string_append(string *self, const char *s);
void string_set(string *self, const char *s);
void string_free(string *self);

#endif // BLASTN_STRING_H