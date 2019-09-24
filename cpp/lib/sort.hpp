#pragma once
#include "../util/types.hpp"

Blastn::SortedSequenceMap sort_filter(Blastn::ExtendedSequenceMap extended_pairs,
                                      Blastn::SequenceMap query,
                                      s32 match,
                                      s32 mismatch,
                                      s32 gap);
