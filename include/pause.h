#ifndef PAUSE_H
#define PAUSE_H

#include "game_state.h"

void pause_init(GameContext *ctx);
void pause_update(GameContext *ctx);
void pause_check(GameContext *ctx);

#endif // PAUSE_H