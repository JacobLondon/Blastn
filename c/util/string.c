#include <stdlib.h>
#include <stdio.h>
#include "string.h"

str *string(const char *value)
{
    int i;

    str *self = malloc(sizeof(str));
    self->size = 0;
    while (*value++)
        self->size++;
    value -= self->size + 1;
    self->c_str = malloc(self->size * sizeof(char));

    for (i = 0; i < self->size; i++)
        self->c_str[i] = value[i];
    
    self->c_str[i] = '\0';
    
    return self;
}

void string_append(str *self, const char *s)
{
    int size = 0;
    int i = 0;

    while (s[size++]);

    self->c_str = realloc(self->c_str, (self->size + size + 1) * sizeof(char));
    while (*s)
        self->c_str[self->size + i++] = *s++;
    
    self->c_str[self->size + i] = '\0';

    self->size = self->size + size - 1;
}

void string_set(str *self, const char *s)
{
    int size = 0;
    int i = 0;

    while (s[size++]);

    if (size != self->size) {
        // clear the old memory
        while (i < self->size)
            self->c_str[i++] = '\0';
        i = 0;
        self->c_str = realloc(self->c_str, (size + 1) * sizeof(char));
        self->size = size - 1;
    }

    while (*s)
        self->c_str[i++] = *s++;
}

void string_free(str *self)
{
    free(self->c_str);
    free(self);
}

static void teststr()
{
    str *mystring = string("wow super cool");
    printf("CSTR: %s\n", mystring->c_str);
    for (int i = 0; i < mystring->size; i++)
        printf("%d\n", mystring->c_str[i]);

    string_append(mystring, ", really!");
    printf("CSTR: %s\n", mystring->c_str);
    for (int i = 0; i < mystring->size; i++)
        printf("%d\n", mystring->c_str[i]);

    printf("CSTR: %s\n", mystring->c_str);
    string_set(mystring, "new string!");
    for (int i = 0; i < mystring->size; i++)
        printf("%d\n", mystring->c_str[i]);

    
    printf("CSTR: %s\n", mystring->c_str);
    for (int i = 0; i < mystring->size; i++)
        printf("%d\n", mystring->c_str[i]);
}
