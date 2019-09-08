#ifndef _BLASTN_TYPES_H
#define _BLASTN_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;
typedef float f32;
typedef double f64;

#define pointer(id) (void *)&(id)
#define ref(type, id) *(type *)(id)


extern const char GAP;
extern const char INVALID;

enum iterable_types {
    U32,
    NODE,
    VECTOR,
    MAP,
};
// TODO add STRING, MATCH, ADJACENT_PAIR, EXTENDED

typedef struct _string {
    char *c_str;
    u32 size;
} string;

typedef struct _vector {
    void *vec;
    u32 type;
    u32 size;
    u32 end;
} vector;

typedef struct _node {
    char *key;
    void *value;
} node;

typedef struct _map {
    vector *buckets;
    u32 type;       // iterable type enum
    u32 size;       // number of buckets
    u32 capacity;   // number of buckets with items
} map;

/**
 * 
 * Blastn types
 * 
 */

typedef struct _match {
    string word;
    vector data_indices;
    vector query_indices;
} match;

match match_init(string word, vector data_indices, vector query_indices);


typedef struct _adjacent_pair {
    string word1, word2;
    u32 length;
    u32 dindex1, dindex2;
    u32 qindex1, qindex2;
} adjacent_pair;

adjacent_pair adjacent_pair_init(string word1, string word2, u32 dindex1, u32 qindex1, u32 dindex2, u32 qindex2);


typedef struct _extended {
    string extended_pair;
    s32 dindex;
} extended;

extended extended_init(string extended_pair, s32 dindex);

/**
 * 
 * Blastn intermediate types
 * 
 */

typedef vector matrix; // vector<vector<u32>>
matrix matrix_init();

typedef map sequence_map; // map<string, string>
sequence_map sequence_map_init();

typedef map indexed_word_map; // map<string, vector<u32>
indexed_word_map indexed_word_map_init();

typedef map indexed_sequence_map; // map<string, indexed_word_map>
indexed_sequence_map indexed_sequence_map_init();

typedef map matched_matches_map; // map<string, vector<Match>>
matched_matches_map matched_matches_map_init();

typedef map matched_sequence_map; // map<string, matched_matches_map>
matched_sequence_map matched_sequence_map_init();

typedef map paired_matches_map; // map<string, vector<adjacent_pair>>
paired_matches_map paired_matches_map_init();

typedef map paired_sequence_map; // map<string, paired_matches_map>
paired_sequence_map paired_sequence_map_init();

typedef map extended_pairs_map; // map<string, vector<extended>>
extended_pairs_map extended_pairs_map_init();

typedef map extended_sequence_map; // map<string, extended_pairs_map>
extended_sequence_map extended_sequence_map_init();

#endif // _BLASTN_TYPES_H