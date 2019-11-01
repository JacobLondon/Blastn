#pragma once

#include "../util/types.hpp"

namespace Blastn {

/**
 * @brief Prepare the extended pairs for being sorted
 */
vector<HSP> format_hsps(ExtendedSequenceMap& extended_pairs,
                        SequenceMap& query,
                        SequenceMap& subject,
                        f32 lambda,
                        f32 kappa,
                        size_t subject_length);

} // Blastn