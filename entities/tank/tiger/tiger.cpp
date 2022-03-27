#include <iostream>
#include "tiger.h"


Tiger::Tiger(Scene *scene, int x, int y) : Tank(scene, x, y) {
    turret_offset_px = 0;
    barrel_offset_px = 60;
    barrel_offset_recoil_px = -10;
    forward_engine_acceleration = 250.0f;
    forward_max_velocity = 150.0f;
    backward_engine_acceleration = 200.0f;
    backward_max_velocity = 100.0f;
    deceleration = 250.0f;
    hull_rotational_acceleration = 1.0f;
    hull_rotational_deceleration = 1.5f;
    hull_max_rotational_velocity = 0.5f;
    turret_max_rotate_speed = 0.3f;
    reload_duration = 3.0f;
    barrel_recoil_reset_duration = 0.8f;
    reload_timer = Timer(reload_duration);
    load_textures();
    load_sounds();
}

void Tiger::load_textures() {
    Resources *resources = scene->get_graphics()->get_resources();
    hull_texture = resources->get_texture("tiger_hull");
    turret_texture = resources->get_texture("tiger_turret");
    barrel_texture = resources->get_texture("tiger_barrel");
}


void Tiger::load_sounds() {
    Resources *resources = scene->get_graphics()->get_resources();
    Sound engine_idle = resources->get_sound("tank/engine_idle");
    Sound engine_accelerate = resources->get_sound("tank/engine_accelerate");
    Sound engine_tracks = resources->get_sound("tank/tracks");
    engine_sound = EngineSound(scene, engine_idle, engine_tracks, engine_accelerate, 1.29f);
    engine_sound.start_engine();
}
