#ifndef BULLETS_H
#define BULLETS_H

#include <stdint.h>

#define W 100
#define H 32
#define MAX_BULLETS 20

typedef struct {
    int x, y;
    int vx, vy;
    int alive;
    int type;  // 0=normal (dies at edge), 1=bouncing (reflects at edge)
} Bullet;

extern Bullet bullets[MAX_BULLETS];

// Initialize bullet system
void bullets_init(void);

// Spawn a new bullet with random angle
void spawn_simple_bullet(void);

// Erase bullets from display
void erase_bullet(void);

// Update bullet positions and check bounds
void update_bullets(void);

// Draw bullets on screen
void draw_bullets(void);

#endif // BULLETS_H
