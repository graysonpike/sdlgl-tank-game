#ifndef TANK_H
#define TANK_H

#include <utility>

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/graphics/texture.h>
#include "engine_sound.h"

class Tank : public PhysicalEntity {

protected:

    virtual void load_textures() = 0;
    virtual void load_sounds() = 0;
    std::pair<float, float> get_turret_center();
    std::pair<float, float> get_barrel_center();
    float get_velocity_ratio();
    float get_rotation_ratio();
    void update_velocity();
    void update_hull_rotational_velocity();
    void update_engine_sound();

    // Constant properties
    int turret_offset_px; // Pixels forward from center of tank to position center of turret
    int barrel_offset_px; // Pixels forward from center of tank to position center of barrel
    int barrel_offset_recoil_px; // Magnitude of offset applied to barrel_offset_px when gun is fired
    float forward_engine_acceleration;
    float forward_max_velocity;
    float backward_engine_acceleration;
    float backward_max_velocity;
    float deceleration;
    float hull_rotational_acceleration;
    float hull_rotational_deceleration;
    float hull_max_rotational_velocity;
    float turret_max_rotate_speed;
    float reload_duration;
    float barrel_recoil_reset_duration; // The time in seconds for the barrel to reset to its default position after recoiling

    // Input control variables
    float throttle;
    float steering;
    float turret_control;

    // Dynamic physics variables
    float hull_angle;
    float turret_angle;
    float velocity;
    float hull_rotational_velocity;
    float barrel_offset_recoil_dynamic_px; // Offset applied to barrel_offset_px during gun recoil

    Timer reload_timer;

    Texture hull_texture;
    Texture turret_texture;
    Texture barrel_texture;

    EngineSound engine_sound;

public:

	Tank(Scene *scene, int x, int y);
    virtual ~Tank()=default;
	void set_throttle(float throttle);
    void set_steering(float steering);
    void set_turret_control(float turret_control);
    void fire();
    void update();
    void render();

};

#endif
