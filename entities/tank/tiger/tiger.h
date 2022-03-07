#include <utility>

#include <sdlgl/game/scene.h>

#include "../tank.h"

class Tiger : public Tank {

    void load_textures();

public:

	Tiger(Scene *scene, int x, int y);
    
};