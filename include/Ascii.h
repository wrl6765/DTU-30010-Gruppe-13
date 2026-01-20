#ifndef ASCII_H_
#define ASCII_H_

#include "30010_io.h"
#include "Physics.h"
#include "bullets.h"
#include "game_state.h"

#define gotoxy(X,Y) printf("\x1B[%d;%dH",(int)(Y),(int)(X))
#define clear() printf("\x1B[2J")
#define hide_cursor() printf("\x1B[?251")

#define BG_DOT "\033[90m%c\033[0m"

#define DISPLAY_HEIGHT  ((uint16_t)0x20)  // 32
#define DISPLAY_WIDTH   ((uint16_t)0x64)  // 100

#define X_COORDINATE    (DISPLAY_WIDTH << 8)
#define Y_COORDINATE    (DISPLAY_HEIGHT << 8)

#define Y_MIN    (1 << 8)
#define Y_MAX    ((DISPLAY_HEIGHT-2) << 8)

#define X_MIN    (1 << 8)
#define X_MAX    ((DISPLAY_WIDTH-2) << 8)

// Alien sprite definition
#define ALIEN_WIDTH   4

// Alien height definitions
#define ALIEN_HEIGHT_LVL_1   3
#define ALIEN_HEIGHT_LVL_2   4
#define ALIEN_HEIGHT_LVL_3   5

// Bullet sizes
#define BULLET_SMALL_HEIGHT   1
#define BULLET_SMALL_WIDTH   2
#define BULLET_MEDIUM_HEIGHT   1
#define BULLET_MEDIUM_WIDTH   3
#define BULLET_LARGE_HEIGHT   3
#define BULLET_LARGE_WIDTH   3

// Powerup sizes
#define POWERUP_WIDTH   5
#define POWERUP_HEIGHT   5

void borders(void);
void bgcolor(uint8_t background);
void drawSaturn(void);
void drawAlien(player *p, GameContext *ctx);
void drawBullet(Bullet *b);
void eraseAlien(player *p, GameContext *ctx);
void drawPowerup(Powerup *pu);
void erasePowerup(Powerup *pu);
void print_level(GameContext *ctx);
void print_score(player *p);
void print_hp(player *p);

#endif /* ASCII_H_ */
