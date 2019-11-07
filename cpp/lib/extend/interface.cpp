#include "interface.hpp"

/**
 * C++ Format
 * Transmission (TX)
 * [u64 Query_Size, u64 GapStartIndex, u64 GapCount, Query_Sequence, Subject_Sequence]
 * 
 * Receive (RX)
 * u64 Result
 * 
 * 
 * FPGA Format
 * Transmission (TX)
 * u64 Result
 * 
 * Receive (RX)
 * [u64 Sequence1_Size, u64 GapStartIndex, u64 GapCount, Query_Sequence, Subject_Sequence]
 * 
 * 
 * FPGA Hardware
 * 3 bits per Query letter, MSB = Gap, others => (00 -> A, 01 -> C, 10 -> G, 11 -> T)
 * Queue which fills with Query (with Gaps) and the Subject
 * Combinational ckt which fills score matrix
 * Transmit highest score, and reset queues and score matrix
 * 
 */

namespace Blastn {

PackedFmt::PackedFmt()
: query_size(0), gap_index(0), gap_count(0), query{0}, subject{0}
{}


void PackedFmt::pack(const char *query, const char *subject, u64 query_size, u64 subject_size)
{
    this->query_size = query_size;
    gap_index  = 0;
    gap_count  = 0;

    u64 i, gap_probe, j, shiftpos;

    // NOTE: If the query / subject's length is not divisible by 4,
    //       then the extraneous values will be ignored for scoring.
    // ALSO: Assume a gap CANNOT start before index 3
    // ALSO: Gaps must ONLY be in the query, not the subject

    for (i = 0, j = 0, shiftpos = 0; i + 3 < query_size && i / 4 < SW_MAX_LENGTH; i += 4) {
        for (gap_probe = 0; gap_probe < 4; gap_probe++) {
            // found first gap
            if (query[i + gap_probe] == CHAR_GAP) {
                if (!gap_index)
                    gap_index = i + gap_probe;
                gap_count++;
                continue;
            }
            
            this->query[j] = this->query[j] | (PACK_FIND(query[i + gap_probe] << ((shiftpos % 4) * 2)));
            shiftpos++;
        }
        // go to the next byte
        if (!(shiftpos % 4))
            j++;
    }

    for (i = 0; i + 3 < subject_size && i / 4 < SW_MAX_LENGTH; i += 4) {
        for (j = 0; j < 4; j++)
            this->subject[i / 4] = this->subject[i / 4] | (PACK_FIND(subject[i + j]) << (j * 2));
    }
}


} // Blastn