#ifndef BULLETS_H
#define BULLETS_H

#include <stdint.h>
#include "game_state.h"
 
#define BULLET_HEIGHT 1
#define BULLET_WIDTH 3
#define MAX_BULLETS 20
typedef struct {
    int x, y;
    int vx, vy;
    int ax, ay;
    int alive;
    int type;  // 0=normal (dies at edge), 1=bouncing (reflects at edge)
    uint8_t max_bullets;
} Bullet;

extern Bullet bullets[MAX_BULLETS];

// Initialize bullet system
void bullets_init(Bullet *b);

// Spawn a new bullet with random angle
void spawn_simple_bullet(Bullet *b);

// Erase bullets from display
void erase_bullet(Bullet *b);

// Update bullet positions and check bounds
void update_bullets(GameContext *ctx, Bullet *b);

// Draw bullets on screen
void draw_bullets(Bullet *b);
#endif // BULLETS_H
