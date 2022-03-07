#include "tank.h"


Tank::Tank(Scene *scene, int x, int y) :
    PhysicalEntity(scene, x, y, 0, 0),
    throttle(0),
    steering(0),
    hull_angle(0),
    turret_angle(0),
    acceleration(std::pair<float, float>(0, 0)),
    velocity(std::pair<float, float>(0, 0)) {

    load_textures();
}

void Tank::load_textures() {}

void Tank::set_throttle(float throttle) {
    this->throttle = throttle;
}

void Tank::set_steering(float steering) {
    this->steering = steering;
}

void Tank::update() {}

void Tank::render() {}
