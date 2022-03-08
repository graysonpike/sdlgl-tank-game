#include <iostream>
#include <sdlgl/input/inputs.h>
#include "player.h"


Player::Player(Scene *scene, Tank *tank) : Entity(scene), tank(tank) {}

void Player::update() {
    Inputs *inputs = scene->get_inputs();

    // Turret Control
    float turret_control = 0.0f;
    if (inputs->is_key_down(SDL_SCANCODE_LEFT)) {
        turret_control -= 1.0f;
    }
    if (inputs->is_key_down(SDL_SCANCODE_RIGHT)) {
        turret_control += 1.0f;
    }
    if (turret_control != 0.0f) {
        tank->set_turret_control(turret_control);
    }

    // Driving Control
    float throttle = 0.0f;
    if (inputs->is_key_down(SDL_SCANCODE_W)) {
        throttle += 1.0f;
    }
    if (inputs->is_key_down(SDL_SCANCODE_S)) {
        throttle -= 1.0f;
    }
    if (throttle != 0) {
        tank->set_throttle(throttle);
    }
}

void Player::render() {}
