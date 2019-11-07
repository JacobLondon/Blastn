#pragma once

#include "../../util/types.hpp"

namespace Blastn {

struct PackedFmt {
    PackedFmt();
    void pack(const char *query, const char *subject, u64 query_size, u64 subject_size);

    u64 query_size;
    u64 gap_index;
    u64 gap_count;
    byte query[SW_MAX_LENGTH];
    byte subject[SW_MAX_LENGTH];

};

}