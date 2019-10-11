#pragma once

class Progress {
public:
    Progress(size_t max);
    size_t iteration = 0;
    size_t max = 0;

    void update();
};
