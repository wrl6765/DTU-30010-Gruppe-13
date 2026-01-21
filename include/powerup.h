#ifndef POWERUP_H_
#define POWERUP_H_
#include "game_state.h"
#include "Physics.h"

void spawn_powerup(player *p, GameContext *ctx);
void powerup_forcefield_init(player *p);
void powerup_forcefield_apply(player *p, Bullet *b);
void powerup_score_multiplier_init(player *p);
void powerup_effects_update(player *p);
void powerup_heal_player(player *p);
void powerups_Update(GameContext *ctx, player *p);


#endif /* POWERUP_H_ */
