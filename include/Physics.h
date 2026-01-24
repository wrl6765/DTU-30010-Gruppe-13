#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "30010_io.h"
#include "game_state.h"
#include "bullets.h"
#include <stdbool.h>
#include <stdint.h>

/* ---------------- POWERUPS ---------------- */

typedef enum {
	POWERUP_NONE = 0,
    POWERUP_HEART = 1,
    POWERUP_FORCEFIELD = 2,
    POWERUP_MULTIPLIER = 3
} PowerupType;

typedef struct {
    int32_t x, y;
    int32_t prev_x, prev_y;
    int32_t vx, vy;
    PowerupType type;
    uint8_t active;     // 1 = on screen, 0 = not present
} Powerup;

/* ---------------- PLAYER ---------------- */

typedef struct player {
    int16_t x, y, vy, ay;
    int16_t score, score_multiplier, highscore;
    int16_t width, height;
    int16_t prev_x, prev_y;
    uint8_t hp;
    uint8_t alien_level;

	// powerup pickups
    Powerup heart_pickup;
    Powerup forcefield_pickup;
    Powerup multiplier_pickup;


	uint16_t forcefield_active; // effect active
	uint16_t multiplier_active; // effect active	
	uint16_t forcefield_timer;
	uint16_t multiplier_timer;

	uint16_t led_timer;

} player;

extern player p;

/* ---------------- FUNCTIONS ---------------- */
// collision detections
bool player_collides_with_bullet(player *p, const Bullet *b);
bool heal_collides_with_player(player *p);
bool multiplier_collides_with_player(player *p);
bool forcefield_collides_with_player(player *p);

void player_init(void);
void update_player(player *p, uint8_t joystick, GameContext *ctx);


#endif /* PHYSICS_H_ */
