#pragma once

#include "../util/types.hpp"

namespace Blastn {

string format_output(vector<HSP>& hsps, SequenceMap& query, SequenceMap& subject, u32 precision);

void write_output(string data, string output_file);

} // Blastn