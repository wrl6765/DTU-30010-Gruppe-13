#ifndef MODE_H
#define MODE_H

#include <stdint.h>

#define GAME_STATE_MENU 0
#define GAME_STATE_PLAY 1
#define GAME_STATE_HELP 2
#define GAME_STATE_GAME_OVER 3
#define GAME_STATE_PAUSE 4

#define MENU_MODE_PLAY 0
#define MENU_MODE_HELP 1
#define MENU_MODE_QUIT 2

// Gamecontext struct, used for various variables that arent connected to the player or bullet
typedef struct GameContext {
    uint8_t game_state; // What state the game is in eg. menu, pause, game over.
    uint8_t menu_mode; // What the cursor is hovering in menu
    uint8_t prev_joystick;
    uint32_t timer_counter;
    uint8_t level;
    uint32_t highscore;
    int16_t joy_ax;// resulting acceleration from joystick
    int16_t joy_ay;
    int16_t joy_x; // joystick positions
    int16_t joy_y;

} GameContext;


void game_state_init(GameContext *ctx); // initialize current game state
void game_state_update(GameContext *ctx, uint8_t joystick); // update current game state
void game_init(GameContext *ctx); // initialize game
void game_loop(GameContext *ctx, uint8_t joystick); // update game

#endif
