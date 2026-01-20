#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "30010_io.h"
#include "game_state.h"
#include <stdbool.h>
#include "bullets.h"


typedef struct{
	int16_t x, y, vy, ay, score, score_multiplier, highscore;
	int16_t width, height;
	int16_t prev_x, prev_y;
	uint8_t hp;
	uint8_t alien_level;
}player;
extern player p;


// Powerup struct
typedef enum {
	POWERUP_HEART = 0,
	POWERUP_SHIELD = 1
} PowerupType;

typedef struct{
	int16_t x, y;   // 8.8
	int16_t prev_x, prev_y;
	PowerupType type;
	uint8_t active;   // 0=inaktiv, 1=aktiv
} Powerup;

bool player_collides_with_bullet(const player *p, const Bullet *b);

void player_init(void);
void update_player(player *p, uint8_t joystick, GameContext *ctx);


#endif /* PHYSICS_H_ */
