#include "scene.h"
#include <random>
#include <iostream>

std::mt19937 gen2(std::chrono::duration_cast<std::chrono::nanoseconds>((std::chrono::high_resolution_clock::now()).time_since_epoch()).count());

Scene::Scene(const std::vector<bird> birds)
    : m_birds(birds)
{
    unsigned int k = 1;
    while (k++) {
        do_smth();
    }
}
double random1(double min, double max)
{
    std::uniform_real_distribution<> r(min, max);
    double result = r(gen2);
    return result;
}

double random2(double c, double sigm)
{
    std::normal_distribution<double> r(c, sigm);
    double result = r(gen2);
    return result;
}
int random(int min, int max)
{
    std::uniform_int_distribution<> r(min, max);
    return r(gen2);
}
void Scene::move_tubes()
{
    --tube1_x;
    if (tube1_x < -51) {
        tube1_x = 549;
        tube1_y = random(50, 510) - 1470;
    }
    --tube2_x;
    if (tube2_x < -51) {
        tube2_x = 549;
        tube2_y = random(50, 510) - 1470;
    }
}

void Scene::find_nearest_tube()
{
    if (tube1_x < 350 && tube1_x > 50) {
        X = tube1_x;
        Y = 1680 + tube1_y;
    }
    else {
        X = tube2_x;
        Y = 1680 + tube2_y;
    }
}
void Scene::check_lives()
{
    for (auto & x: m_birds) {
        if (x.is_dead(tube1_x, tube1_y, tube2_x, tube2_y))
            x.is_alive = false;
    }
}

bool Scene::all_dead()
{
    size_t k = 0;
    while (k < m_birds.size() && m_birds[k].is_alive == 0)
        ++k;
    if (k == m_birds.size())
        return 1;
    return 0;
}

bool cmp(const bird & a, const bird & b) {
    return a.score < b.score;
}
void Scene::mutations()
{
    for (size_t i = m_birds.size() / 10; i < 8 * m_birds.size() / 10; ++i) {
        m_birds[i].net.g = m_birds[i % (m_birds.size() / 10)].net.rel_mutation(0.025);
        m_birds[i].score = 0;
    }
    for (size_t i = 8 * m_birds.size() / 10; i < m_birds.size(); ++i) {
        m_birds[i].net = NeuroNet({4,3,1});// = Neuro_net({4, 5, 3, 1});
        m_birds[i].score = 0;
    }
}
void Scene::reset()
{
    for (size_t i = 0; i < m_birds.size(); ++i) {
        m_birds[i].reset_position();
        m_birds[i].score = 0;
    }
    tube1_x = 0;
    tube2_x = 300;
    tube1_y = -1200;
    tube2_y = -1300;
}

void Scene::new_gen()
{
    gen_num++;
    sort(m_birds.rbegin(), m_birds.rend(), cmp);
    max_score = std::max(max_score, m_birds[0].score);
    std::cout << gen_num << ": " << m_birds[0].score << "(" << max_score << ")\n";
    reset();
    mutations();
}


void Scene::do_smth()
{
    move_tubes();
    find_nearest_tube();
    check_lives();
    for (auto & x : m_birds) {
        if (x.is_alive) {
            bool need_jump = x.need_to_jump(X, Y);
            x.move(need_jump);
        }
    }
    if (all_dead()) {
        new_gen();
    }
}
