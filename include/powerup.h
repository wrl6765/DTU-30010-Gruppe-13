#ifndef POWERUP_H
#define POWERUP_H

#include "Physics.h"

// Player repel powerup - repels bullets away in random direction when they contact player
void powerup_repel_bullets(player *p);

void powerup_score_multiplier(player *p, GameContext *ctx);
void powerup_heal_player(player *p);
#endif // POWERUP_H
