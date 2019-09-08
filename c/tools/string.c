#include <stdlib.h>
#include <stdio.h>
#include "string.h"

string *string_init(u32 size)
{
    int i;

    string *self = malloc(sizeof(string));
    self->size = 0;
    self->size = size;
    self->c_str = malloc((size + 1) * sizeof(char));

    for (i = 0; i < self->size + 1; i++)
        self->c_str[i] = '\0';
    
    return self;
}

void string_append(string *self, const char *s)
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

void string_set(string *self, const char *s)
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

    // set the string
    while (*s)
        self->c_str[i++] = *s++;
}

void string_free(string *self)
{
    free(self->c_str);
    free(self);
}

/**
 * test
 */

static void string_test()
{
    string *mystring = string_init("wow super cool");
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
