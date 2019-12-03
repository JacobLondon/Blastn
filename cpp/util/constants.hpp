#pragma once

#include <string>

namespace Blastn {

/**
 * Byte packing utilities
 */

// MUST be divisible by 4
// The equivalent is g_SIZE in VHDL
#define SW_MAX_LENGTH 12

enum Pack {
    A = 0,
    C = 1,
    G = 2,
    T = 3,
};

#define PACK_LOOKUP "ACGT"

#define PACK_FIND(letter) \
      ((letter) == PACK_LOOKUP[0] ? Pack::A \
    : ((letter) == PACK_LOOKUP[1] ? Pack::C \
    : ((letter) == PACK_LOOKUP[2] ? Pack::G \
    : Pack::T)))

/**
 * Specify which smith waterman implementation to use in extend
 */
enum SW {
    NO_PRESERVE_MEM,
    PRESERVE_MEM,
    MULTI_THREAD,
    FPGA,
};

/**
 * Constants used throughout Blastn
 */

const std::string STR_GAP = "-";
const char CHAR_GAP = '-';
const std::string INVALID = "\0";

}
