#pragma once
#include <string>

namespace Blastn {

#define SW_MAX_LENGTH 2000

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
