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
    velocity(0),
    engine_sound(scene)
    {}

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

    if (throttle != 0.0f || steering != 0.0f) {
        engine_sound.accelerate();
    }
    else {
        engine_sound.stop_accelerate();
    }

    turret_angle += turret_control * turret_max_rotate_speed * delta;
    turret_control = 0.0f;

    // Update velocity according to throttle
    if (throttle > 0.0f) {
        velocity += throttle * forward_engine_acceleration * delta;
    }
    if (throttle < 0.0f) {
        velocity += throttle * backward_engine_acceleration * delta;
    }
    if (steering == 0.0f) {
        velocity = Math::clamp(velocity, -backward_max_velocity, forward_max_velocity);
    }
    else {
        float speed_penalty_ratio = (1.0f - (0.2f * abs(steering)));
        velocity = Math::clamp(velocity, -backward_max_velocity * speed_penalty_ratio, forward_max_velocity * speed_penalty_ratio);
    }
    if (throttle == 0.0f) {
        if (velocity > 0.0f) {
            velocity -= deceleration * delta;
            velocity = std::max(velocity, 0.0f);
        }
        if (velocity < 0.0f) {
            velocity += deceleration * delta;
            velocity = std::min(velocity, 0.0f);
        }
    }
    throttle = 0.0f;

    // Update angle according to steering
    float angle_change = steering * hull_rotation_speed;
    hull_angle += angle_change;
    turret_angle += angle_change;
    steering = 0.0f;


    // Move tank according to angle and velocity
    std::pair<float, float> position_change = Math::rotate_vector(velocity, hull_angle);
    x += position_change.first * delta;
    y += position_change.second * delta;
}

void Tank::render() {
    hull_texture.draw(scene, x, y, hull_angle);
    std::pair<float, float> turret_pos = get_turret_center();
    std::pair<float, float> barrel_pos = get_barrel_center();
    barrel_texture.draw(scene, barrel_pos.first, barrel_pos.second, turret_angle);
    turret_texture.draw(scene, turret_pos.first, turret_pos.second, turret_angle);
}
