#include <iostream>
#include "tiger.h"


Tiger::Tiger(Scene *scene, int x, int y) : Tank(scene, x, y) {
    barrel_offset_px = 60;
    forward_engine_acceleration = 200.0f;
    forward_engine_acceleration_cutoff_velocity = 50.0f;
    backward_engine_acceleration = -100.0f;
    backward_engine_acceleration_cutoff_velocity = 30.0f;
    turret_max_rotate_speed = 0.3f;
    load_textures();
}

void Tiger::load_textures() {
    Resources *resources = scene->get_graphics()->get_resources();
    hull_texture = resources->get_texture("tiger_hull");
    turret_texture = resources->get_texture("tiger_turret");
    barrel_texture = resources->get_texture("tiger_barrel");
}
