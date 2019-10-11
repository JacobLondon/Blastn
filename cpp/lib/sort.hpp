#pragma once
#include "../util/types.hpp"

namespace Blastn {

ExtendedSequenceMap sort_filter(ExtendedSequenceMap extended_pairs,
                                SequenceMap query,
                                s32 match,
                                s32 mismatch,
                                s32 gap);

} // Blastn