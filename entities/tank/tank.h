#include <utility>

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/graphics/texture.h>

class Tank : public PhysicalEntity {

protected:

    virtual void load_textures();

    const int turret_offset_px = 0;

    float throttle;
    float forward_engine_acceleration;
    float forward_engine_acceleration_cutoff_velocity;
    float backward_engine_acceleration;
    float backward_engine_acceleration_cutoff_velocity;
    float steering;
    float hull_angle;
    float turret_angle;
    std::pair<float, float> acceleration;
    std::pair<float, float> velocity;

    Texture hull_texture;
    Texture turret_texture;

public:

	Tank(Scene *scene, int x, int y);
    virtual ~Tank()=default;
	void set_throttle(float throttle);
    void set_steering(float steering);
    void update();
    void render();
    

};