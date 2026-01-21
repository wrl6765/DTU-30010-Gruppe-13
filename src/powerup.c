#include "Physics.h"
#include "bullets.h"
#include "Ascii.h"
#include <math.h>
#include <stdint.h>
#include "game_state.h"
#include <stdbool.h>
#include "powerup.h"

void spawn_powerup(player *p, GameContext *ctx) {
    uint32_t t = ctx->timer_counter;

   if ((t+600) % 900 == 0 && !p->heart_pickup.active) {
        p->heart_pickup.active = 1;
        p->heart_pickup.type = POWERUP_HEART;
        p->heart_pickup.x = DISPLAY_WIDTH << 8;
        p->heart_pickup.y = 5 << 8;
        p->heart_pickup.vx = -128;
        p->heart_pickup.vy = 0;
    }
    

    if ((t+300) % 900 == 0 && !p->forcefield_pickup.active) {
        // spawn forcefield
        p->forcefield_pickup.active = 1;
        p->forcefield_pickup.type = POWERUP_FORCEFIELD;
        p->forcefield_pickup.x = DISPLAY_WIDTH << 8;
        p->forcefield_pickup.y = 12 << 8;
        p->forcefield_pickup.vx = -128;
        p->forcefield_pickup.vy = 0;
    }

    if (t % 900 == 0 && !p->multiplier_pickup.active) {
        // spawn multiplier
        p->multiplier_pickup.active = 1;
        p->multiplier_pickup.type = POWERUP_MULTIPLIER;
        p->multiplier_pickup.x = DISPLAY_WIDTH << 8;
        p->multiplier_pickup.y = 20 << 8;
        p->multiplier_pickup.vx = -128;
        p->multiplier_pickup.vy = 0;
    }
}

void powerup_heal_player(player *p) { //should be called when there is collision with heal powerup
        p->hp += 2; // Heal 2 HP
        if (p->hp > 5) {  // Assuming max HP is 5
            p->hp = 5;
        }
}

void powerup_score_multiplier_init(player *p) { //should be called when there is collision with score multiplier powerup
            p->score_multiplier = 2;  // Double score
            p->multiplier_active = 1;
            p->multiplier_timer = 300;  // Set timer for 300 ticks
    
}


void powerup_forcefield_init(player *p) { //should be called when there is collision with forcefield powerup
            p->forcefield_active = 1;
            p->forcefield_timer = 300;
        
   
}

void powerup_effects_update(player *p) {
    //------multiplier effect update------
    {
    if (p->multiplier_timer > 0) {
        p->multiplier_timer--;
        if (p->multiplier_timer == 0) {
            p->score_multiplier = 1;  // Reset to normal score
            p->multiplier_active = 0;
        }
    }
}
    //------forcefield effect update------
    if (p->forcefield_timer > 0) {
        p->forcefield_timer--;
        if (p->forcefield_timer == 0) {
            p->forcefield_active = 0;
        }
    }
}
void powerup_forcefield_apply(player *p, Bullet *b) {
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

    const float EFFECT_RADIUS = 15; // pixels
    if (dist < EFFECT_RADIUS) {
        float nx = dx_pix / dist;
        float ny = dy_pix / dist;

        // Strength scales with proximity: closer -> stronger push
        // Tweak the constant to get desired gameplay feel
        float strength_pixels = (EFFECT_RADIUS - dist) * 0.005f; // pixels/tick^2

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
}


// Updates powerups using random test powerups
// Bevæger sig vandret og bouncer af vægge (hvis vi vil bruge denne funktion)
void powerups_Update(GameContext *ctx, player *p) {
    // Only do anything if the game is in play mode
    

    // --- Erase old powerups ---
    if (p->heart_pickup.active)
        erasePowerup(p);
    if (p->forcefield_pickup.active)
        erasePowerup(p);
    if (p->multiplier_pickup.active)
        erasePowerup(p);


    // --- move ---
 if (p->heart_pickup.active) {
        p->heart_pickup.prev_x = p->heart_pickup.x;
        p->heart_pickup.prev_y = p->heart_pickup.y;
        p->heart_pickup.x += p->heart_pickup.vx;
        p->heart_pickup.y += p->heart_pickup.vy;
    }

    if (p->forcefield_pickup.active) {
        p->forcefield_pickup.prev_x = p->forcefield_pickup.x;
        p->forcefield_pickup.prev_y = p->forcefield_pickup.y;
        p->forcefield_pickup.x += p->forcefield_pickup.vx;
        p->forcefield_pickup.y += p->forcefield_pickup.vy;
    }

    if (p->multiplier_pickup.active) {
        p->multiplier_pickup.prev_x = p->multiplier_pickup.x;
        p->multiplier_pickup.prev_y = p->multiplier_pickup.y;
        p->multiplier_pickup.x += p->multiplier_pickup.vx;
        p->multiplier_pickup.y += p->multiplier_pickup.vy;
    }
    //---------collision-----------
     if (p->heart_pickup.active && heal_collides_with_player(p)) {
        p->heart_pickup.active = 0;
        powerup_heal_player(p);
    }

    if (p->multiplier_pickup.active && multiplier_collides_with_player(p)) {
        p->multiplier_pickup.active = 0;
        powerup_score_multiplier_init(p);
    }

    if (p->forcefield_pickup.active && forcefield_collides_with_player(p)) {
        p->forcefield_pickup.active = 0;
        powerup_forcefield_init(p);
    }

    //---------border checks-----------
    if ((p->heart_pickup.x >> 8) < -POWERUP_WIDTH) {
    p->heart_pickup.active = 0;
}
    if ((p->forcefield_pickup.x >> 8) < -POWERUP_WIDTH) {
    p->forcefield_pickup.active = 0;
    }
    if ((p->multiplier_pickup.x >> 8) < -POWERUP_WIDTH) {
    p->multiplier_pickup.active = 0;
    }

    // --- Draw updated powerups ---
    if (p->heart_pickup.active)
        drawPowerup(p);
    if (p->forcefield_pickup.active)
        drawPowerup(p);
    if (p->multiplier_pickup.active)
        drawPowerup(p);

}


