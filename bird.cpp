#include "bird.h"

bird::bird()
    :net(NeuroNet({4, 3, 1}))
{
    reset_position();
}

double norm(double value, double min, double max) {
    return 2 * (value - min) / (max - min) - 1;
}
double norm2(double value, double min, double max) {
    return (value - min) / (max - min);
}

void bird::reset_position ()
{
    is_alive = true;
    e = 0;
    v = 0;
    x = 100;
    y = 200;
}

void bird::dbg__dump (std::ostream & /*ofs*/)
{

}
bool bird::is_dead(int tube1_x, int tube1_y, int tube2_x, int tube2_y)
{
    if ((x > tube1_x - 30 && x < tube1_x + 51) && (y > 1680 + tube1_y - 30 || y < tube1_y + 1500)){
        return 1;
    }
    if ((x > tube2_x - 30 && x < tube2_x + 51) && (y > 1680 + tube2_y - 30 || y < tube2_y + 1500)){
        return 1;
    }
    if (y > 767) {
        return 1;
    }
}

bool bird::need_to_jump(int X, int Y)
{

    net.neu[0].value = norm(X - x, -50, 250); //50 - 100 350 - 100
    net.neu[1].value = norm2(Y - y, 260, 720);//
    net.neu[2].value = norm(v, -5, 3);
    net.neu[3].value = norm2(767 - y, 0, 767);
//    b_log << "==Input: \n"
//          << "x-dist to tube: " << net.neu[0].value << "\n"
//          << "y-dist to tube: " << net.neu[1].value << "\n"
//          << "speed         : " << net.neu[2].value << "\n"
//          << "altitude      : " << net.neu[3].value << "\n";

//    b_log << "==Sinapses: \n";// << net << "\n";
//    b_log << *(net);// <<"\n";
    net.getAns();
    return (net.neu.back().activated_value > 0);
//    b_log << "==Res: " << net->neu.back().activated_value
//          << (need_jump ? " jump!" : "")
//          << "\n\n";
}

void bird::move(bool need_jump)
{
    score += 10;
    if (need_jump) {
        v = 3;
    }
    net.clear_values();
    y -= v;
    if (e == 30) {
        v -= 1;
        e = 0;
    }
    else {
        e += 1;
    }

}
