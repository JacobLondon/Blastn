#pragma once

/**
 * Blastn include file
 */

#include "dust.hpp"
#include "hsp.hpp"
#include "prepare.hpp"
#include "match.hpp"
#include "output.hpp"
#include "pairs.hpp"
#include "sort.hpp"
#include "split.hpp"
#include "extend/extend.hpp"
#include "extend/interface.hpp"
#include "extend/smith_waterman.hpp"

namespace Blastn {

int test(std::vector<std::string> args);
int blastn(std::vector<std::string> args);

} // Blastn