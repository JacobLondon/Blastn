#include "interface.hpp"

/**
 * C++ Format
 * Transmission (TX)
 * [u32 Query_Size, u32 GapStartIndex, u32 GapCount, Query_Sequence, Subject_Sequence]
 * 
 * Receive (RX)
 * u64 Result
 * 
 * 
 * FPGA Format
 * Transmission (TX)
 * u32 Result
 * 
 * Receive (RX)
 * [u32 Query_Size, u32 GapStartIndex, u32 GapCount, Query_Sequence, Subject_Sequence]
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
: size{0}, gap_index{0}, gap_count{0}, query{0}, subject{0}
{}

PackedFmt::~PackedFmt()
{}

static const u32 BYTE1 = 0x000000FFu;
static const u32 BYTE2 = 0x0000FF00u;
static const u32 BYTE3 = 0x00FF0000u;
static const u32 BYTE4 = 0xFF000000u;

void PackedFmt::pack(const char *query, const char *subject, u32 size)
{
    this->size[0] = (BYTE1 & size) >> 0;
    this->size[1] = (BYTE2 & size) >> 8;
    this->size[2] = (BYTE3 & size) >> 16;
    this->size[3] = (BYTE4 & size) >> 24;
    u32 gap_index_tmp = 0;
    u32 gap_count_tmp  = 0;

    u32 i, gap_probe, j, shiftpos;

    // NOTE: If the query / subject's length is not divisible by 4,
    //       then the extraneous values will be ignored for scoring.
    // ALSO: Assume a gap CANNOT start before index 3
    // ALSO: Gaps must ONLY be in the query, not the subject

    for (i = 0, j = 0, shiftpos = 0; i + 3 < size && i / 4 < SW_MAX_LENGTH; i += 4) {
        for (gap_probe = 0; gap_probe < 4; gap_probe++) {
            // found first gap
            if (query[i + gap_probe] == CHAR_GAP) {
                if (!gap_index)
                    gap_index_tmp = i + gap_probe;
                gap_count_tmp++;
                continue;
            }
            
            this->query[j] = this->query[j] | (PACK_FIND(query[i + gap_probe] << ((shiftpos % 4) * 2)));
            shiftpos++;
        }
        // go to the next byte
        if (!(shiftpos % 4))
            j++;
    }

    // extract gap_count and gap_index
    this->gap_count[0] = (BYTE1 & gap_count_tmp) >> 0;
    this->gap_index[0] = (BYTE1 & gap_index_tmp) >> 0;
    this->gap_count[1] = (BYTE2 & gap_count_tmp) >> 8;
    this->gap_index[1] = (BYTE2 & gap_index_tmp) >> 8;
    this->gap_count[2] = (BYTE3 & gap_count_tmp) >> 16;
    this->gap_index[2] = (BYTE3 & gap_index_tmp) >> 16;
    this->gap_count[3] = (BYTE4 & gap_count_tmp) >> 24;
    this->gap_index[3] = (BYTE4 & gap_index_tmp) >> 24;

    // query 
    for (i = 0; i + 3 < size && i / 4 < SW_MAX_LENGTH; i += 4) {
        for (j = 0; j < 4; j++)
            this->subject[i / 4] = this->subject[i / 4] | (PACK_FIND(subject[i + j]) << (j * 2));
    }
}


} // Blastn