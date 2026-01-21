#ifndef BULLETS_H
#define BULLETS_H

#include <stdint.h>

typedef struct GameContext GameContext;  // forward declaration OK

#define MAX_BULLETS 20
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

void bullets_init(void);
void spawn_simple_bullet(void);
void erase_bullet(void);
void update_bullets(GameContext *ctx);
void draw_bullets(void);
void max_bullets(GameContext *ctx);

#endif
