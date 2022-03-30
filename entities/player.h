#ifndef PLAYER_H
#define PLAYER_H

#include <sdlgl/game/entity.h>

#include "tank/tank.h"

class Player : public Entity {

    Tank *tank;

public:

	Player(Scene *scene, Tank *tank);
    void update() override;
    void render() override;
    
};

#endif
