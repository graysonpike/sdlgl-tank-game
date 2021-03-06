#include "enemy.h"
#include <iostream>
#include "math.h"
#include "hit_counter.h"


Enemy::Enemy(Scene *scene, float x, float y) : Tiger(scene, x, y) {
	std::vector<Entity*> players = scene->get_entities_of_type(1);
	player = static_cast<Player*>(players[0]);
}

void Enemy::handle_driving() {

}

void Enemy::handle_turret() {
	std::pair<int, int> player_position = player->get_position();
	float target_angle = atan2(player_position.second - y, player_position.first - x);
	target_angle += M_PI / 2;
	if (target_angle > M_PI) {
		target_angle = -M_PI + target_angle - M_PI;
	}
	if (turret_angle > M_PI) {
		turret_angle = -M_PI + turret_angle - M_PI;
	} else if (turret_angle < -M_PI) {
		turret_angle = M_PI - (turret_angle + M_PI);
	}



	bool direction;
	if (target_angle > turret_angle) {
		if (target_angle - turret_angle > M_PI) {
			direction = false;
		} else {
			direction = true;
		}
	} else {
		if (turret_angle - target_angle > M_PI) {
			direction = true;
		} else {
			direction = false;
		}
	}
	rotate_turret(direction);
}

void Enemy::handle_fire() {
	std::pair<int, int> fire_endpoint = get_fire_endpoint();
	if (player->get_hitbox()->check_point((SDL_Point){fire_endpoint.first, fire_endpoint.second})) {
		fire();
	}
}


void Enemy::update() {
    handle_driving();
    handle_turret();
    handle_fire();
    Tiger::update();
}


void Enemy::fire() {
	if (reload_timer.is_done()) {
		std::vector<Entity*> players = scene->get_entities_of_type(4);
        HitCounter *counter = static_cast<HitCounter*>(players[0]);
        counter->increment();
	}
	Tank::fire();
}