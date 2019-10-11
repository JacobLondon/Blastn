#include <iostream>
#include "display.hpp"

Progress::Progress(size_t max)
    : iteration{ 0 }, max{ max }
{}

void Progress::update()
{
    iteration++;
    std::printf("\r[%d / %d]", (int)iteration, (int)max);
    fflush(stdout);
    if (iteration == max)
        std::cout << std::endl;
}
