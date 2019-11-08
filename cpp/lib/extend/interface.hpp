#pragma once

#include "../../util/types.hpp"

namespace Blastn {

struct PackedFmt {
    PackedFmt();

    /**
     * @brief Fill PackedFmt's data with each character of query and subject into 4 letters per byte
     * @param query        The query sequence which is being extended and needs scoring
     * @param subject      The subject sequence which the query is being extended to
     * @param query_size   The length of the query
     * @param subject_size The length of the subject
     */
    void pack(const char *query, const char *subject, u64 query_size, u64 subject_size);

    u64 query_size;
    u32 gap_index;
    u32 gap_count;
    byte query[SW_MAX_LENGTH];
    byte subject[SW_MAX_LENGTH];
};

}