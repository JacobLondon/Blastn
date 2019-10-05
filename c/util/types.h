#ifndef BLASTN_TYPES_H
#define BLASTN_TYPES_H

#include <stdio.h>
#include <string.h>

typedef struct vector_s {
    unsigned int *memory;
    unsigned int end;
} Vector;

typedef struct node_s {
    char *key;
    void *value;
} Node;

typedef struct hash_table_s {
    Node *memory;
} HashTable;

typedef struct match_s {
    char *word;
    Vector *data_indices;
    Vector *query_indices;
} Match;

typedef struct adjacent_pair_s {
    char *word1;
    char *word2;
    unsigned int length;
    unsigned int dindex1, dindex2;
    unsigned int qindex1, qindex2;
} AdjacentPair;

typedef struct extended_s {
    char *extended_pair;
    unsigned int dindex;
    unsigned int qindex;
} Extended;

typedef struct sorted_s {
    char *extended_pair;
    unsigned int dindex, qindex;
    signed int score;
} Sorted;

#define Vector(T) Vector
#define HashTable(T, U) HashTable

#define Matrix Vector(Vector(unsigned int))
void print_matrix(Matrix m);

#define SequenceMap HashTable(char *, char *)
void print_sequence_map(SequenceMap m);

#define IndexedWordMap HashTable(char *, Vector(unsigned int))
#define IndexedSequenceMap HashTable(char *, IndexedWordMap)
void print_indexed_sequence_map(IndexedSequenceMap m);

#define MatchedMatchesMap HashTable(char *, Vector(Match))
#define MatchedSequenceMap HashTable(char *, MatchedMatchesMap)
void print_matched_sequence_map(MatchedSequenceMap m);

#define PairedMatchesMap HashTable(char *, Vector(AdjacentPair))
#define PairedSequenceMap HashTable(char *, PairedMatchesMap)
void print_paired_sequence_map(PairedSequenceMap m);

#define ExtendedPairsMap HashTable(char *, Vector(Extended))
#define ExtendedSequenceMap HashTable(char *, ExtendedPairsMap)
void print_extended_sequence_map(ExtendedSequenceMap m);

#define SortedPairsMap HashTable(char *, Vector(Sorted));
#define SortedSequenceMap HashTable(char *, SortedPairsMap)
void print_sorted_sequence_map(SortedSequenceMap m);

#endif // BLASTN_TYPES_H