#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "bsp/30010_io.h"

typedef struct{
	int16_t x, y, vy, ay, score, highscore;
	uint8_t hp;
	uint8_t alien_level;
}player;


// Bullet struct
typedef struct{
	int16_t x, y;   // 8.8
	uint8_t type;   // 1=regular, 2=bouncing, 3=cannonball, 4=sniper
	uint8_t size;   // 1=small, 2=medium, 3=large
}bullet;

extern player p;

void update_player(player *p, uint8_t joystick);

void player_init(void);

#endif /* PHYSICS_H_ */
