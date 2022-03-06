#include <sdlgl/game/scene.h>
#include <sdlgl/game/physical_entity.h>

class Tank : public PhysicalEntity {

    float throttle;
    float steering;

public:

	Tank(Scene *scene, int x, int y);
    virtual ~Tank()=default;
	virtual void set_throttle(float throttle) = 0;
    virtual void set_steering(float steering) = 0;
    

};