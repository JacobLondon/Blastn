#include <stdlib.h>  // calloc, free
#include <string.h>  // memcpy
#include "prepare.h"
#include "../tools/map.h"
#include "../tools/string.h"
#include "../util/globals.h"

sequence_map *build_sequence(char *path, char sep)
{
    sequence_map *result = map_init(STRING);
    char *name;
    char *line;
    FILE *fp = fopen(path, 'r');
    char *line = calloc(BlastnMaxLineWidth, sizeof(char));

    if (!fp) {
        fprintf(stderr, "Failure: Could not open: %s\n", path);
        exit(-1);
    }

    while (fgets(line, sizeof(line), fp)) {
        // a new sequence name is found
        if (line[0] == sep) {
            // set the new name (sep char is length 1)
            name = calloc(sizeof(line), sizeof(char));
            memcpy(name, line, sizeof(line));

            // pair the sequence name iwth an empty build string
            string *value = string_init(1);
            string_set(value, "");
            map_insert(result, node_init(name, pointer_to(value)));
        }
        // the if statement MUST have been entered first
        else {
            // append the next line of sequence data to the build string
            string_append(map_at(result, name), line);
        }
    }

    // don't free name, it holds the latest data in result
    free(line);
    fclose(fp);
    return result;
}

indexed_sequence_map *split_sequence(sequence_map *data, u32 length)
{

}

indexed_sequence_map *prepare_sequence(char *path, u32 length, char sep)
{

}
