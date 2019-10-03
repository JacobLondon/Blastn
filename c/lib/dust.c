#include "dust.h"
#include "split.h"

/**
 * return false as soon as the strings are not the same
 * will return true if one string is longer, but they were equal until the end
 *      ie. ABCD123 will equal ABCD, this should not happen in the use case
 */
static inline bool same(const char *s1, const char *s2)
{
    for (; s1 && s2; s1++, s2++) {
        if (*s1 != *s2)
            return false;
    }
    return true;
}

static uint32_t count(const char *begin, const char *end, char *value)
{
    uint32_t count = 0;
    for (char *iter = begin; iter != end; iter++) {
        if (same(iter->c_str, value->c_str)) {
            count++;
        }
    }
    return count;
}

float dust(char *word, uint32_t pattern_len)
{
    float total_score = 0;
    uint32_t occurrence;
    vector(string) *triplets = split_to_words(word, pattern_len);
    map(char *, uint32_t) *record = map_init(I32);
    map_resize(record, triplets->size * 2);

    for (string *triplet = vector_begin(triplets); triplet != vector_end(string, triplets); triplet++) {
        // triplet not recorded yet
        if (map_at(record, triplet->c_str) == NULL) {
            // count occurrences
            occurrence = count(vector_begin(triplets), vector_end(string, triplets), triplet);
            occurrence = occurrence * (occurrence - 1) / 2;
            map_insert(record, node_init(triplet->c_str, voidptr(occurrence)));
        }
    }
    // sum the scores
    node *n;
    map_for_each(record, n) {
        total_score += ref(uint32_t, n->value);
    }

    vector_free(triplets);
    map_free(record);

    return total_score / (strlen(word) - pattern_len);
}

IndexedSequenceMap *dust_filter(IndexedSequenceMap *data, float threshold, uint32_t pattern_len, uint32_t word_len)
{
    indexed_sequence_map *result = map_init(MAP);

    // breaks words into subsequences of triplets
    node *qname_seqmap;
    map_for_each(data, qname_seqmap) {
        indexed_word_map *temp = map_init(VECTOR);
        node *word_indices;
        map_for_each((map *)qname_seqmap->value, word_indices) {
            if (dust(word_indices->key, pattern_len))
                map_insert(temp, node_init(word_indices->key, word_indices->value));
        }
        if (temp->capacity > 0)
            map_insert(result, node_init(qname_seqmap->key, temp));
        else
            map_free(temp);
    }
    return result;
}
