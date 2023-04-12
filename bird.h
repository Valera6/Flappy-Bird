#pragma once

#include <algorithm>
#include <vector>
#include "neuro_net.h"

#include <memory>

class bird {
public:
//    std::unique_ptr<NeuroNet> net;
    NeuroNet net;
    int score = 0;
    bool is_alive;
    int x;
    int y;
    double v;
    double e;

    bird();

    void reset_position();

    void dbg__dump(std::ostream & /*ofs*/);

    void move(bool need_jump);

    bool need_to_jump(int X, int Y);

    bool is_dead(int tube1_x, int tube1_y, int tube2_x, int tube2_y);
};
