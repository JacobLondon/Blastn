#pragma once
#include "../util/types.hpp"

namespace Blastn {

/**
 * @brief Prepare the extended pairs for being sorted
 */
FormattedSequenceMap format_data(ExtendedSequenceMap& extended_pairs);

string format_output(FormattedSequenceMap& s, SequenceMap& data);

void write_output(string& output, string filename);

} // Blastn