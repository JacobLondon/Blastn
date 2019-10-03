#include <stdlib.h>  // calloc, free
#include <string.h>  // memcpy
#include "prepare.h"
#include "../tools/map.h"
#include "../tools/string.h"
#include "../tools/vector.h"
#include "../util/globals.h"
#include "split.h"

sequence_map *build_sequence(char *path, char sep)
{
    sequence_map *result = map_init(STRING);
    char *name;
    char *line;
    FILE *fp = fopen(path, 'r');
    char *line = calloc(BlastnMaxWidth, sizeof(char));

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
            map_insert(result, node_init(name, voidptr(value)));
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
    indexed_sequence_map *result = map_init(MAP);

    // traverse the sequence
    node *name_seqmap;
    map_for_each(result, name_seqmap) {
        // get all words and find their indices in that data set
        indexed_word_map *indexed_words = map_init(STRING);
        vector(string) *words = split_to_words(name_seqmap->value, length);

        // map each word to all of their indices each time the word appears
        string *word = vector_begin(words);
        for (u32 i = 0; word != vector_end(string, words); word++, i++) {
            u32 *index = malloc(sizeof(u32));
            *index = i;
            // insert the index if the item doesn't exist
            if (map_at(indexed_words, word) == NULL) {
                vector(u32) *vec = vector_init(I32, 1);
                vector_append(vec, index);
                map_insert(indexed_words, node_init(word->c_str, vec));
            }
            else
                vector_append(map_at(indexed_words, word), index);
        }
        map_insert(result, node_init(name_seqmap->key, indexed_words));
    }
    return result;
}

indexed_sequence_map *prepare_sequence(char *path, u32 length, char sep)
{
    sequence_map *build_data = build_sequence(path, sep);
    indexed_sequence_map *indexed_data = split_sequence(build_data, length);

    return indexed_data;
}
