#pragma once

#include "../../util/types.hpp"

namespace Blastn {

struct FPGA_Format {
    FPGA_Format(u64 query_size, u64 gap_index, u64 gap_count, byte *query, byte *subject);

    u64 query_size;
    u64 gap_index;
    u64 gap_count;
    byte *query;
    byte *subject;
};

FPGA_Format pack(char *data);

}