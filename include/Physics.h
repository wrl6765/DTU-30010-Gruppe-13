#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "30010_io.h"
#include "game_state.h"
#include "bullets.h"
#include <stdbool.h>
#include <stdint.h>

/* ---------------- POWERUPS ---------------- */

typedef enum {
    POWERUP_HEART = 0,
    POWERUP_FORCEFIELD = 1,
    POWERUP_MULTIPLIER = 2
} PowerupType;

typedef struct Powerup {
    int16_t x, y;        // 8.8 fixed point
    int16_t prev_x, prev_y;
    int16_t vx, vy;
    PowerupType type;
    uint8_t active;
} Powerup;

/* ---------------- PLAYER ---------------- */

typedef struct player {
    int16_t x, y, vy, ay;
    int16_t score, score_multiplier, highscore;
    int16_t width, height;
    int16_t prev_x, prev_y;
    uint8_t hp;
    uint8_t alien_level;

    Powerup heart;
    Powerup forcefield;
    Powerup multiplier;

    int heart_dir;
    int forcefield_dir;
    uint8_t forcefield_active;
} player;

extern player p;

/* ---------------- FUNCTIONS ---------------- */

bool player_collides_with_bullet(const player *p, const Bullet *b);

void player_init(void);
void update_player(player *p, uint8_t joystick, GameContext *ctx);

void powerup_forcefield(player *p, Bullet *b, GameContext *ctx);
void powerup_score_multiplier(player *p, GameContext *ctx);
void powerup_heal_player(player *p);

#endif /* PHYSICS_H_ */
