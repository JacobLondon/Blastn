#include "smith_waterman.h"
#include "../util/globals.h"
#include "../tools/vector.h"
#include "../tools/map.h"
#include "../tools/string.h"

enum direction {
    _INVALID,
    LEFT,
    UP,
    DIAG,
};

typedef struct _score_tuple {
    u32 index;
    s32 value;
} score_tuple;

static inline score_tuple max(s32 left, s32 up, s32 diag)
{
    score_tuple max = { 0, 0 };

    if (left > 0) {
        max.value = left;
        max.index = LEFT;
    }
    if (up > max.value) {
        max.value = up;
        max.index = UP;
    }
    if (diag > max.value) {
        max.value = diag;
        max.index = DIAG;
    }

    return max;
}

static inline s32 score_alignment(char alpha, char beta, s32 match, s32 mismatch, s32 gap)
{
    if (alpha == beta)
        return match;
    else if (BlastnGap == alpha || BlastnGap == beta)
        return gap;
    else
        return mismatch;
}

s32 smith_waterman(string *seq1,
                   string *seq2,
                   s32 match,
                   s32 mismatch,
                   s32 gap)
{
    u32 rows = seq1->size;
    u32 cols = seq2->size;
    u32 i = 0;
    u32 j = 0;

    matrix *score_matrix = vector_init(VECTOR, cols);
    matrix *point_matrix = vector_init(VECTOR, cols);

    for (i = 0; i <= cols; i++) {
        vector_append(score_matrix, vector_init(I32, rows + 1));
        vector_append(point_matrix, vector_init(I32, rows + 1));
    }

    s32 max_score = 0;
    u32 imax = 1;
    u32 jmax = 0;
    s32 left, up, diag;
    score_tuple greatest;

    // fill score matrix
    for (i = 1; i <= cols; i++) {
        for (j = 1; j <= rows; j++) {

            // determine possible score for the current cell
            left = matrix_at(score_matrix, i - 1, j) + gap;
            up   = matrix_at(score_matrix, i, j - 1) + gap;
            diag = matrix_at(score_matrix, i - 1, j - 1)
                 + score_alignment(seq1->c_str[i - 1], seq2->c_str[j - 1], match, mismatch, gap);

            // find greatest
            greatest = max(left, up, diag);
            matrix_at(point_matrix, i, j) = greatest.index;
            matrix_at(score_matrix, i, j) = greatest.value;

            // record high score
            if (matrix_at(score_matrix, i, j) >= max_score) {
                imax = i;
                jmax = j;
                max_score = matrix_at(score_matrix, i, j);
            }
        }
    }

    vector_free(score_matrix);
    vector_free(point_matrix);

    return max_score;
}

indexed_sequence_map *smith_waterman_filter(indexed_sequence_map *data, s32 minscore, s32 match, s32 mismatch, s32 gap)
{
    indexed_sequence_map *result = map_init(MAP);

    node *name_seqmap;
    map_for_each(data, name_seqmap) {
        node *word_indices;
        indexed_word_map *temp = map_init(VECTOR);
        map_for_each((map(char *, sequence_map) *)name_seqmap->value, word_indices) {
            string *word = string_init(word_indices->key);
            if (smith_waterman(word, word, match, mismatch, gap, true) >= minscore) {
                // TODO: does this work properly?
                map_insert(temp, node_init(name_seqmap->key, word_indices->value));
            }
        }
        map_insert(result, node_init(name_seqmap->key, temp));
    }
    //free(data)?
    return result;
}
