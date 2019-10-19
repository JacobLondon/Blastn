#include <string.h>

#include "util.h"

int strfind(char *needle, char **haystack, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        int found = 1;
        for (int j = 0; j < strlen(haystack[i]) && j < strlen(needle); j++) {
            if (needle[i] != haystack[i]) {
                found = 0;
                break;
            }
        }
        if (found)
            return 1;
    }
    return 0;
}