#include "dust.h"
#include "split.h"
#include "../tools/vector.h"
#include "../tools/map.h"

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

static u32 count(const string *begin, const string *end, string *value)
{
    u32 count = 0;
    for (string *iter = begin; iter != end; iter++) {
        if (same(iter->c_str, value->c_str)) {
            count++;
        }
    }
    return count;
}

f32 dust(string *word, u32 pattern_len)
{
    f32 total_score = 0;
    u32 occurrence;
    vector(string) triplets = *split_to_words(word, pattern_len);
    map(char *, u32) record = *map_init(I32);
    map_resize(&record, triplets.size * 2);

    for (string *triplet = vector_begin(triplets); triplet != vector_end(string, triplets); triplet++) {
        // triplet not recorded yet
        if (map_at(&record, triplet->c_str) == NULL) {
            // count occurrences
            occurrence = count(vector_begin(triplets), vector_end(string, triplets), triplet);
            occurrence = occurrence * (occurrence - 1) / 2;
            map_insert(&record, node_init(triplet->c_str, pointer_to(occurrence)));
        }
    }
    // sum the scores
    node *n;
    map_for_each(&record, n) {
        total_score += ref(u32, n->value);
    }

    vector_free(&triplets);
    map_free(&record);

    return total_score / (word->size - pattern_len);
}
