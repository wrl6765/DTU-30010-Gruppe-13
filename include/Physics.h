#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "bsp/30010_io.h"

typedef struct{
	int16_t x, y, vy, ay, score, highscore;
	uint8_t hp;

	}player;

void update_player(player *p);

void player_init(void);

#endif /* PHYSICS_H_ */
