#include "tank.h"


Tank::Tank(Scene *scene, int x, int y) : PhysicalEntity(scene, x, y, 0, 0), throttle(0), steering(0) {}