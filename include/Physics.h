#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "30010_io.h"

typedef struct{
	int16_t x, y, vy, ay, score, highscore;
	uint8_t hp;
	uint8_t alien_level;
}player;

extern player p
// Bullet struct
typedef struct{
	int16_t x, y;   // 8.8
	uint8_t type;   // 1=regular, 2=bouncing, 3=cannonball, 4=sniper
	uint8_t size;   // 1=small, 2=medium, 3=large
}bullet;

void update_player(player *p);

void player_init(player *p);

#endif /* PHYSICS_H_ */
