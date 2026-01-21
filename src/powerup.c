#include "Physics.h"
#include "bullets.h"
#include "Ascii.h"
#include <math.h>
#include <stdint.h>
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
void powerup_forcefield(const player *p, Bullet *b, GameContext *ctx, Powerup *forcefield) { //should be called when there is collision with forcefield powerup
    uint32_t timer = ctx->timer_counter;
    if (timer % 300 == 0) {
        forcefield->active = 0;  // Deactivate forcefield after 300 ticks
    }

    /*
     * Positions are stored in 8.8 fixed point. Convert to pixel floats,
     * compute a normalized direction from player->bullet and apply a
     * small acceleration (in 8.8 fixed point) away from the player when
     * inside an effect radius.
     */
    int32_t player_center_x = (int32_t)p->x + ((int32_t)p->width << 8);
    int32_t player_center_y = (int32_t)p->y + ((int32_t)p->height << 8);
    int32_t bullet_center_x = (int32_t)b->x + ((int32_t)BULLET_WIDTH << 8);
    int32_t bullet_center_y = (int32_t)b->y + ((int32_t)BULLET_HEIGHT << 8);

    int32_t dx_fixed = bullet_center_x - player_center_x; // fixed 8.8
    int32_t dy_fixed = bullet_center_y - player_center_y; // fixed 8.8

    float dx_pix = dx_fixed / 256.0f;
    float dy_pix = dy_fixed / 256.0f;
    float dist = sqrtf(dx_pix * dx_pix + dy_pix * dy_pix);
    if (dist <= 0.0f) return; // safety

    const float EFFECT_RADIUS = 20.0f; // pixels
    if (dist < EFFECT_RADIUS) {
        float nx = dx_pix / dist;
        float ny = dy_pix / dist;

        // Strength scales with proximity: closer -> stronger push
        // Tweak the constant to get desired gameplay feel
        float strength_pixels = (EFFECT_RADIUS - dist) * 0.5f; // pixels/tick^2

        // Convert to 8.8 fixed point for ax/ay
        int ax_fixed = (int)(nx * strength_pixels * 256.0f);
        int ay_fixed = (int)(ny * strength_pixels * 256.0f);

        // Apply acceleration away from player (add because nx points from player->bullet)
        b->ax += ax_fixed;
        b->ay += ay_fixed;
    } else {
        // Outside effect radius: reset acceleration to 0
        b->ax = 0;
        b->ay = 0;
    }

// Updates powerups using random test powerups
// Bevæger sig vandret og bouncer af vægge (hvis vi vil bruge denne funktion)
void powerupsUpdate(GameContext *ctx, Powerup *heart, Powerup *forcefield, Powerup *multiplier, int *heart_dir, int *forcefield_dir) {
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

    if (!forcefield->active) {
        forcefield->x = 50 << 8;
        forcefield->y = 12 << 8;
        forcefield->prev_x = forcefield->x;
        forcefield->prev_y = forcefield->y;
        forcefield->type = POWERUP_FORCEFIELD;
        forcefield->active = 1;
    }

        if (!multiplier->active) {
        multiplier->x = 50 << 8;
        multiplier->y = 12 << 8;
        multiplier->prev_x = multiplier->x;
        multiplier->prev_y = multiplier->y;
        multiplier->type = POWERUP_MULTIPLIER;
        multiplier->active = 1;
    }
    
/*
    // --- Erase old powerups ---
    erasePowerup(heart);
    erasePowerup(forcefield);
    erasePowerup(multiplier);

    // --- Move powerups horizontally ---
    heart->x += (*heart_dir) << 8;
    forcefield->x += (*forcefield_dir) << 8;
    multiplier->x += (*forcefield_dir) << 8;

    // --- Bounce off screen edges ---
    if ((heart->x >> 8) <= 1 || (heart->x >> 8) >= DISPLAY_WIDTH - POWERUP_WIDTH)
        *heart_dir *= -1;

    if ((forcefield->x >> 8) <= 1 || (forcefield->x >> 8) >= DISPLAY_WIDTH - POWERUP_WIDTH)
        *forcefield_dir *= -1;

    // --- Draw updated powerups ---
    drawPowerup(heart);
    drawPowerup(forcefield);
    drawPowerup(multiplier);
}


Dette kan bruges senere i main loopet

// Define powerups and directions
Powerup heart = {.active = 0};
Powerup forcefield = {.active = 0};
int heart_dir = 1;
int forcefield_dir = -1;

// In your main loop (inside tim2_flag)
testPowerupsUpdate(&ctx, &heart, &forcefield, &heart_dir, &forcefield_dir);

*/
}}