#ifndef MODE_H
#define MODE_H

#include <stdint.h>

#define GAME_STATE_MENU 0
#define GAME_STATE_PLAY 1
#define GAME_STATE_HELP 2
#define GAME_STATE_GAME_OVER 3

#define MENU_MODE_PLAY 0
#define MENU_MODE_HELP 1
#define MENU_MODE_QUIT 2

typedef struct GameContext {
    uint8_t game_state;
    uint8_t menu_mode;
    uint8_t prev_joystick;
    uint8_t prev_sw1;
    uint32_t timer_counter;
    uint8_t level;
    uint32_t highscore;
} GameContext;

void game_state_init(GameContext *ctx);
void game_state_update(GameContext *ctx, uint8_t joystick);
void game_init(GameContext *ctx);
void game_loop(GameContext *ctx, uint8_t joystick);

#endif
