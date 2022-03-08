#include <iostream>

#include "tank.h"

#include <sdlgl/utilities/math.h>


Tank::Tank(Scene *scene, int x, int y) :
    PhysicalEntity(scene, x, y, 0, 0),
    turret_offset_px(0),
    barrel_offset_px(0),
    throttle(0),
    steering(0),
    turret_control(0),
    hull_angle(0),
    turret_angle(0),
    barrel_recoil_offset_px(0),
    acceleration(std::pair<float, float>(0, 0)),
    velocity(std::pair<float, float>(0, 0)) {}

std::pair<float, float> Tank::get_turret_center() {
    std::pair<float, float> pos = Math::rotate_vector(turret_offset_px, hull_angle);
    pos.first += x;
    pos.second += y;
    return pos;
}

std::pair<float, float> Tank::get_barrel_center() {
    std::pair<float, float> pos = Math::rotate_vector(barrel_offset_px + barrel_recoil_offset_px, turret_angle);
    pos.first += x;
    pos.second += y;
    return pos;
}

void Tank::set_throttle(float throttle) {
    this->throttle = throttle;
}

void Tank::set_steering(float steering) {
    this->steering = steering;
}

void Tank::set_turret_control(float turret_control) {
    this->turret_control = turret_control;
}

void Tank::update() {

    float delta = scene->get_delta();

    // Turret Control
    turret_angle += turret_control * turret_max_rotate_speed * delta;
    turret_control = 0.0f;

    // Driving Control
    float velocity_magnitude = Math::magnitude(velocity);
    if (throttle > 0.0f && velocity_magnitude < forward_engine_acceleration_cutoff_velocity) {
        std::pair<float, float> engine_acceleration = Math::rotate_vector(forward_engine_acceleration, hull_angle);
        acceleration = Math::add_vectors(acceleration, engine_acceleration);
    }
    if (throttle < 0.0f && velocity_magnitude < backward_engine_acceleration_cutoff_velocity) {
        std::pair<float, float> engine_acceleration = Math::rotate_vector(backward_engine_acceleration, hull_angle);
        acceleration = Math::add_vectors(acceleration, engine_acceleration);
    }
    throttle = 0.0f;

    // Acceleration and Velocity
    // std::cout << acceleration.first;
    std::pair<float, float> velocity_change = Math::scale_vector(acceleration, delta);
    velocity = Math::add_vectors(velocity, velocity_change);
    x += velocity.first * delta;
    y += velocity.second * delta;
    acceleration.first = 0.0f;
    acceleration.second = 0.0f;
    
}

void Tank::render() {
    hull_texture.draw(scene, x, y, hull_angle);
    std::pair<float, float> turret_pos = get_turret_center();
    std::pair<float, float> barrel_pos = get_barrel_center();
    barrel_texture.draw(scene, barrel_pos.first, barrel_pos.second, turret_angle);
    turret_texture.draw(scene, turret_pos.first, turret_pos.second, turret_angle);
}
