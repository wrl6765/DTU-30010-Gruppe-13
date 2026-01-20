#include "Physics.h"
#include "bullets.h"
#include "Ascii.h"
#include <math.h>
#include "game_state.h"
#include "powerup.h"
#include <stdbool.h>

void powerup_heal_player(player *p) { //should be called when there is collision with heal powerup
    p->hp += 2; // Heal 2 HP
    if (p->hp > 5) {  // Assuming max HP is 5
        p->hp = 5;
    }
}

void powerup_score_multiplier(player *p, GameContext *ctx) { //should be called when there is collision with score multiplier powerup
    uint32_t timer = ctx->timer_counter; 
    p->score_multiplier = 2;  // Double score
    if (timer % 300 == 0)
    {
        p->score_multiplier = 1;  // Reset to normal after 300 ticks
    }

}
// Player repel powerup - repels bullets away in random direction when they contact player
void powerup_forcefield(const player *p, Bullet *b, GameContext *ctx) {
    uint32_t timer = ctx->timer_counter;
    if (timer % 300 == 0)
    {
        ctx->forcefield_active = 0;  // Deactivate forcefield after 300 ticks
    }
    int player_center_x = p->x + (p->width << 7); // Center x in 8.8 format
    int player_center_y = p->y + (p->height << 7); // Center y in 8.8 format

    int bullet_center_x = b->x + (BULLET_WIDTH << 7); // Center x in 8.8 format
    int bullet_center_y = b->y + (BULLET_HEIGHT << 7); // Center y in 8.8 format

    int16_t dx = bullet_center_x - player_center_x;
    int16_t dy = bullet_center_y - player_center_y;
    
    float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance == 0) return; // Prevent division by zero
    if (distance < 20 << 8) { // If within 20 pixels
        b->ax = -1/(dx); // Repel away
        b->ay = -1/(dy);
    }
}

// Updates powerups using random test powerups
// Bevæger sig vandret og bouncer af vægge (hvis vi vil bruge denne funktion)
void powerupsUpdate(GameContext *ctx, Powerup *heart, Powerup *shield, int *heart_dir, int *shield_dir) {
    // Only do anything if the game is in play mode
    if (ctx->game_state != GAME_STATE_PLAY) return;

    // Initialize powerups if they are inactive (test values)
    if (!heart->active) {
        heart->x = 10 << 8;
        heart->y = 5 << 8;
        heart->prev_x = heart->x;
        heart->prev_y = heart->y;
        heart->type = POWERUP_HEART;
        heart->active = 1;
    }

    if (!shield->active) {
        shield->x = 50 << 8;
        shield->y = 12 << 8;
        shield->prev_x = shield->x;
        shield->prev_y = shield->y;
        shield->type = POWERUP_SHIELD;
        shield->active = 1;
    }

    // --- Erase old powerups ---
    erasePowerup(heart);
    erasePowerup(shield);

    // --- Move powerups horizontally ---
    heart->x += (*heart_dir) << 8;
    shield->x += (*shield_dir) << 8;

    // --- Bounce off screen edges ---
    if ((heart->x >> 8) <= 1 || (heart->x >> 8) >= DISPLAY_WIDTH - POWERUP_WIDTH)
        *heart_dir *= -1;

    if ((shield->x >> 8) <= 1 || (shield->x >> 8) >= DISPLAY_WIDTH - POWERUP_WIDTH)
        *shield_dir *= -1;

    // --- Draw updated powerups ---
    drawPowerup(heart);
    drawPowerup(shield);
}

/*
Dette kan bruges senere i main loopet

// Define powerups and directions
Powerup heart = {.active = 0};
Powerup shield = {.active = 0};
int heart_dir = 1;
int shield_dir = -1;

// In your main loop (inside tim2_flag)
testPowerupsUpdate(&ctx, &heart, &shield, &heart_dir, &shield_dir);

*/
