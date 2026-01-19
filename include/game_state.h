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
} GameContext;


void game_state_init(GameContext *ctx);
void game_state_update(GameContext *ctx, uint8_t joystick);
void game_init(void);
void game_loop(void);
void menu_state_init(void);
void help_state_init(void);

#endif