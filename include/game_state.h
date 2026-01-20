#ifndef MODE_H
#define MODE_H

#include <stdint.h>

#define GAME_STATE_MENU 0
#define GAME_STATE_PLAY 1
#define GAME_STATE_HELP 2

#define MENU_MODE_PLAY 0
#define MENU_MODE_HELP 1
#define MENU_MODE_QUIT 2
    
typedef struct {
    uint8_t game_state;
    uint8_t menu_mode;
    uint8_t prev_joystick;
    uint32_t timer_counter;
    uint8_t level;
    uint32_t highscore;
} GameContext;


void game_state_init(GameContext *ctx);
void game_state_update(GameContext *ctx, uint8_t joystick);
void game_init(GameContext *ctx);
void game_loop(GameContext *ctx, uint8_t joystick);
void menu_state_init(void);
void help_state_init(void);


#endif