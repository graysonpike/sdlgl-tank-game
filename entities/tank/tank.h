#ifndef TANK_H
#define TANK_H

#include <utility>

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/graphics/texture.h>

class Tank : public PhysicalEntity {

protected:

    virtual void load_textures() = 0;
    std::pair<float, float> get_turret_center();
    std::pair<float, float> get_barrel_center();

    // Constant properties
    int turret_offset_px;
    int barrel_offset_px;
    float forward_engine_acceleration;
    float forward_engine_acceleration_cutoff_velocity;
    float backward_engine_acceleration;
    float backward_engine_acceleration_cutoff_velocity;
    float turret_max_rotate_speed;

    // Input control variables
    float throttle;
    float steering;
    float turret_control;

    // Dynamic physics variables
    float hull_angle;
    float turret_angle;
    float barrel_recoil_offset_px;
    std::pair<float, float> acceleration;
    std::pair<float, float> velocity;

    Texture hull_texture;
    Texture turret_texture;
    Texture barrel_texture;

public:

	Tank(Scene *scene, int x, int y);
    virtual ~Tank()=default;
	void set_throttle(float throttle);
    void set_steering(float steering);
    void set_turret_control(float turret_control);
    void update();
    void render();

};

#endif
