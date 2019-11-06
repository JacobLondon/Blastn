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

FPGA_Format::FPGA_Format(u64 query_size, u64 gap_index, u64 gap_count, byte query[SW_MAX_LENGTH], byte subject[SW_MAX_LENGTH])
: query_size(query_size), gap_index(gap_index), gap_count(gap_count), query(query), subject(subject)
{}

FPGA_Format pack(char *data)
{
    
}

} // Blastn