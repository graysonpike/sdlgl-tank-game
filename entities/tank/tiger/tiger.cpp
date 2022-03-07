#include <iostream>
#include "tiger.h"


Tiger::Tiger(Scene *scene, int x, int y) : Tank(scene, x, y) {
    forward_engine_acceleration = 0;
    forward_engine_acceleration_cutoff_velocity = 0;
    backward_engine_acceleration = 0;
    backward_engine_acceleration_cutoff_velocity = 0;
}

void Tiger::load_textures() {
    std::cout << "Textures loaded" << std::endl;
}
