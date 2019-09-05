#include <stdio.h>
#include "util/string.h"

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

int main()
{
    teststr();

    return 0;
}