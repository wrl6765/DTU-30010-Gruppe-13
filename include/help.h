#ifndef HELP_H_
#define HELP_H_
#include "game_state.h"

void displayHelpScreen();
void help_update(GameContext *ctx, uint8_t joystick);
void gameoverscreen(GameContext *ctx, uint8_t joystick);
#endif /* HELP_H_ */