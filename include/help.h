#ifndef HELP_H_
#define HELP_H_
#include "game_state.h"

void displayHelpScreen();
void help_update(GameContext *ctx, uint8_t joystick);
<<<<<<< HEAD
void game_over_update(GameContext *ctx, uint8_t joystick);
void game_over_init(GameContext *ctx);
=======
void game_over_init(GameContext *ctx);
void game_over_update(GameContext *ctx, uint8_t joystick);
>>>>>>> 0e7c0aa882a08f7d3b05976bfdaeafe8e320fdb0
#endif /* HELP_H_ */