//#include "mainwindow.h"

#include "bird.h"
#include "scene.h"
#include <vector>


int main()
{
    size_t num_of_birds = 20;
    std::vector <bird> birds(num_of_birds);
    Scene mainScene(birds);
    return 0;
}
