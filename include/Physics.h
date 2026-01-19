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

// Bouncing bullet struct - bounces at frame edges with random chance spawn
typedef struct {
	int x, y;
	int vx, vy;
	int alive;
	int type;  // 0=normal (dies at edge), 1=bouncing (reflects at edge)
	int ax,ay;
} BouncingBullet;


typedef struct Cannonball
{
	int16_t x,y;
	int16_t type;
	int16_t vy,vx;
	int16_t ax,ay;
} cannonball;

typedef struct sniper
{
	int16_t x,y;
	int16_t type;
	int16_t vy,vx;
	int16_t ax,ay;
} sniper;



extern player p;

void update_player(player *p, uint8_t joystick);

void player_init(void);

#endif /* PHYSICS_H_ */
