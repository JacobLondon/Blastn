#pragma once

/**
 * Blastn include file
 */

#include "dust.hpp"
#include "extend.hpp"
#include "prepare.hpp"
#include "match.hpp"
#include "pairs.hpp"
#include "smith_waterman.hpp"
#include "sort.hpp"
#include "split.hpp"

namespace Blastn {

int test(int argc, char **argv);
int blastn(int argc, char **argv);

} // Blastn