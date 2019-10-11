#include <algorithm>
#include <iterator>
#include "lib/blastn.hpp"

int main(int argc, char **argv)
{
    std::vector<std::string> args{ argv + 1, argv + argc };
    bool test = std::find(std::begin(args), std::end(args), "-test") != std::end(args);

    if (!test)
        Blastn::blastn(args);
    else
        Blastn::test(args);
    
    return 0;
}