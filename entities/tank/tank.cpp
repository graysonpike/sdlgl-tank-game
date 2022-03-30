#include <iostream>

#include "tank.h"

#include <sdlgl/utilities/math.h>


Tank::Tank(Scene *scene, int x, int y) :
    PhysicalEntity(scene, x, y, 0, 0),
    throttle(0),
    steering(0),
    turret_control(0),
    hull_angle(0),
    turret_angle(0),
    velocity(0),
    hull_rotational_velocity(0),
    engine_sound(scene),
    barrel_offset_recoil_dynamic_px(0)
    {}

std::pair<float, float> Tank::get_turret_center() {
    std::pair<float, float> pos = Math::rotate_vector(turret_offset_px, hull_angle);
    pos.first += x;
    pos.second += y;
    return pos;
}

std::pair<float, float> Tank::get_barrel_center() {
    std::pair<float, float> pos = Math::rotate_vector(barrel_offset_px + barrel_offset_recoil_dynamic_px, turret_angle);
    pos.first += x;
    pos.second += y;
    return pos;
}

float Tank::get_velocity_ratio() {
    if (velocity > 0) {
        return velocity / forward_max_velocity;
    }
    else if (velocity < 0) {
        return -velocity / backward_max_velocity;
    }
    else {
        return 0.0f;
    }
}

float Tank::get_rotation_ratio() {
    return std::abs(hull_rotational_velocity) / hull_max_rotational_velocity;
}

void Tank::update_velocity() {
    float delta = scene->get_delta();
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
    // Apply deceleration when no throttle is applied
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
}

void Tank::update_hull_rotational_velocity() {
    float delta = scene->get_delta();
    if (steering > 0.0f) {
        hull_rotational_velocity += steering * hull_rotational_acceleration * delta;
    }
    if (steering < 0.0f) {
        hull_rotational_velocity += steering * hull_rotational_acceleration * delta;
    }
    hull_rotational_velocity = Math::clamp(hull_rotational_velocity, -hull_max_rotational_velocity, hull_max_rotational_velocity);
    // Apply deceleration if no steering is applied
    if (steering == 0.0f) {
        if (hull_rotational_velocity > 0.0f) {
            hull_rotational_velocity -= hull_rotational_deceleration * delta;
            hull_rotational_velocity = std::max(hull_rotational_velocity, 0.0f);
        }
        if (hull_rotational_velocity < 0.0f) {
            hull_rotational_velocity += hull_rotational_deceleration * delta;
            hull_rotational_velocity = std::min(hull_rotational_velocity, 0.0f);
        }
    }
    steering = 0.0f;
}

void Tank::update_engine_sound() {
    engine_sound.set_tracks_intensity(std::min(0.5f + (get_velocity_ratio() / 2.0f + get_rotation_ratio() / 2.0f), 1.0f));
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

void Tank::fire() {
    if (reload_timer.is_active()) {
        return;
    }
    reload_timer.reset();
    scene->get_audio()->play_sound(cannon_fire_sound, false, 0.8f);
}

void Tank::update() {

    float reload_duration_elapsed = reload_timer.duration_elapsed();
    if (reload_timer.is_active() && reload_duration_elapsed < barrel_recoil_reset_duration) {
        float barrel_reset_ratio = reload_duration_elapsed / barrel_recoil_reset_duration;
        barrel_offset_recoil_dynamic_px = barrel_offset_recoil_px * (1.0f - barrel_reset_ratio);
    }
    else {
        barrel_offset_recoil_dynamic_px = 0;
    }

    // Flip steering when reversing
    if (throttle < 0.0f) {
        steering = -steering;
    }

    float delta = scene->get_delta();

    update_engine_sound();

    turret_angle += turret_control * turret_max_rotate_speed * delta;
    turret_control = 0.0f;

    update_velocity();
    update_hull_rotational_velocity();

    // Move tank according to angle and velocity
    float hull_angle_change = hull_rotational_velocity * delta;
    hull_angle += hull_angle_change;
    turret_angle += hull_angle_change;
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
