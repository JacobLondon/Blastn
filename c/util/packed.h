#ifndef BLASTN_PACKED_H
#define BLASTN_PACKED_H

// word of length 11: 2 bits per letter, 22 bits total
// A: 00, C: 01, G: 10, T: 11

#define EMPTY_MASK 0x3FF
#define A_MASK 0b00
#define C_MASK 0b01
#define G_MASK 0b10
#define T_MASK 0b11

typedef union packed_word_s {
    struct unpacked {
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
         * footer describes bits
         * 0bXX XXXX 1011 : d0-10 used
         * 0bXX XXXX 1010 : d0-9  used
         * ...
         * 0bXX XXXX 0001 : d0    used
         * 0bXX XXXX 0000 : all used
         * 
         * 0bXX 1011 XXXX : d0-10 is a gap
         * 0bXX 1010 XXXX : d0-9  is a gap
         * ...
         * 0bXX 0001 XXXX : d0    is a gap
         * 0bXX 0000 XXXX : no gaps
         */
        unsigned int footer : 10;
    };
    // quick reference
    unsigned int word;
} PackedWord;

unsigned int packed_word_init(char *word, unsigned char length);


#endif // BLASTN_PACKED_H