#ifndef BLASTN_TYPES_H
#define BLASTN_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Collections-C/src/include/array.h>
#include <Collections-C/src/include/hashtable.h>

typedef struct MatchTag {
    char *word;
    Array *data_indices;
    Array *query_indices;
} Match;

typedef struct adjacent_pair_s {
    char *word1;
    char *word2;
    uint32_t length;
    uint32_t dindex1, dindex2;
    uint32_t qindex1, qindex2;
} AdjacentPair;

typedef struct extended_s {
    char *extended_pair;
    uint32_t dindex;
    uint32_t qindex;
} Extended;

typedef struct sorted_s {
    char *extended_pair;
    uint32_t dindex, qindex;
    int32_t score;
} Sorted;

#define Array(T) Array
#define HashTable(T, U) HashTable

#define Matrix Array(Array(uint32_t))
void print_matrix(Matrix m);

#define SequenceMap HashTable(char *, char *)
void print_sequence_map(SequenceMap m);

#define IndexedWordMap HashTable(char *, Array(uint32_t))
#define IndexedSequenceMap HashTable(char *, IndexedWordMap)
void print_indexed_sequence_map(IndexedSequenceMap m);

#define MatchedMatchesMap HashTable(char *, Array(Match))
#define MatchedSequenceMap HashTable(char *, MatchedMatchesMap)
void print_matched_sequence_map(MatchedSequenceMap m);

#define PairedMatchesMap HashTable(char *, Array(AdjacentPair))
#define PairedSequenceMap HashTable(char *, PairedMatchesMap)
void print_paired_sequence_map(PairedSequenceMap m);

#define ExtendedPairsMap HashTable(char *, Array(Extended))
#define ExtendedSequenceMap HashTable(char *, ExtendedPairsMap)
void print_extended_sequence_map(ExtendedSequenceMap m);

#define SortedPairsMap HashTable(char *, Array(Sorted));
#define SortedSequenceMap HashTable(char *, SortedPairsMap)
void print_sorted_sequence_map(SortedSequenceMap m);

#endif // BLASTN_TYPES_H