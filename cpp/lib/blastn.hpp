#pragma once

/**
 * Blastn include file
 */

#include "dust.hpp"
#include "extend.hpp"
#include "hsp.hpp"
#include "prepare.hpp"
#include "match.hpp"
#include "output.hpp"
#include "pairs.hpp"
#include "smith_waterman.hpp"
#include "sort.hpp"
#include "split.hpp"

namespace Blastn {

int test(std::vector<std::string> args);
int blastn(std::vector<std::string> args);

} // Blastn