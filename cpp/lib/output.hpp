#pragma once
#include "../util/types.hpp"

namespace Blastn {

/**
 * @brief Prepare the extended pairs for being sorted
 */
FormattedSequenceMap format_data(ExtendedSequenceMap& extended_pairs);

/**
 * @brief convert the formatted data to each query mapped to the formatted string output
 */
SequenceMap format_output(FormattedSequenceMap& s, SequenceMap& data);

void write_output(SequenceMap& output, string dirname, string extension);

} // Blastn