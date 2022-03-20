#ifndef TIGER_H
#define TIGER_H

#include <utility>

#include <sdlgl/game/scene.h>

#include "../tank.h"

class Tiger : public Tank {

    void load_textures();
    void load_sounds();

public:

	Tiger(Scene *scene, int x, int y);
    
};

#endif
