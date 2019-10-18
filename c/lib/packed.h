#ifndef BLASTN_PACKED_H
#define BLASTN_PACKED_H

// word of length 11: 2 bits per letter, 22 bits total
// A: 00, C: 01, G: 10, T: 11

#define PACKED_WORD_UNUSED 0x3FF

#define PACKED_MAX_LENGTH 11
#define A_CONV 0b00
#define C_CONV 0b01
#define G_CONV 0b10
#define T_CONV 0b11

typedef union packed_word_u {
    struct unpacked_s {
        /**
         * 11 letters
         */
        unsigned int d0  : 2;
        unsigned int d1  : 2;
        unsigned int d2  : 2;
        unsigned int d3  : 2;
        unsigned int d4  : 2;
        unsigned int d5  : 2;
        unsigned int d6  : 2;
        unsigned int d7  : 2;
        unsigned int d8  : 2;
        unsigned int d9  : 2;
        unsigned int d10 : 2;
        /**
         * used describes bits in use
         * 0bXX XXXX 1010 : d0-10 used
         * 0bXX XXXX 1001 : d0-9  used
         * ...
         * 0bXX XXXX 0000 : d0    used
         */
        unsigned int used : 4;
        /**
         * gaps describes which bits are gaps
         * 0bXX 1010 XXXX : d0-10 is a gap
         * 0bXX 1001 XXXX : d0-9  is a gap
         * ...
         * 0bXX 0000 XXXX : d0    is a gap
         */
        unsigned int gaps : 4;
        // Don't Care
        unsigned int DC   : 2;
    } unpack;
    // quick reference
    unsigned int word;
} PackedWord;

/**
 * word A word from the sequence with only letters 'A', 'C', 'G', 'T'
 * length The word length (max of 11)
 */
unsigned int pack(const char *word, unsigned char length);


#endif // BLASTN_PACKED_H