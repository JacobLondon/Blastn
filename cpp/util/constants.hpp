#pragma once

#include <string>

namespace Blastn {

// MUST be divisible by 4
#define SW_MAX_LENGTH 2000

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

enum SW {
    NO_PRESERVE_MEM,
    PRESERVE_MEM,
    MULTI_THREAD,
    FPGA,
};

const std::string STR_GAP = "-";
const char CHAR_GAP = '-';
const std::string INVALID = "\0";

}
