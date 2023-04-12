#pragma once

#include "bird.h"

#include <vector>

class Scene
{
public:
    Scene(std::vector<bird> birds);

    void do_smth();
    void move_tubes();
    void find_nearest_tube();
    void check_lives();
    bool all_dead();
    void new_gen();
    void mutations();
    void reset();

private:
    std::vector<bird> m_birds;

    unsigned int t = 1;

    int tube1_x = 0;
    int tube2_x = 300;
    int tube1_y = -1200;
    int tube2_y = -1300;
    int X;
    int Y;
    int gen_num = 0;
    int max_score = 0;
};
