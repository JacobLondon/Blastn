#pragma once
#include "../util/types.hpp"

namespace Blastn {

string format_output(vector<HSP>& hsps, SequenceMap& subject);

void write_output(string data, string output_file);

} // Blastn