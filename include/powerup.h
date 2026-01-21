#ifndef POWERUP_H
#define POWERUP_H

#include "Physics.h"
#include "bullets.h"

// Player repel powerup - repels bullets away in random direction when they contact player
void powerup_forcefield(const player *p, Bullet *b, GameContext *ctx, Powerup *forcefield);

void powerup_score_multiplier(player *p, GameContext *ctx);
void powerup_heal_player(player *p);
#endif // POWERUP_H
