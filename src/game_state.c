#include "game_state.h"
#include "menu.h"
#include "help.h"
#include "Ascii.h"
#include "HAL.h"
#include "bullets.h"
#include "Physics.h"
#include "charset.h"
#include "heart.h"
#include "powerup.h"

static BulletSystem bullet_system;

void game_state_init(GameContext *ctx)
{
    clear();

    switch (ctx->game_state) {

        case GAME_STATE_MENU:
            ctx->menu_mode = MENU_MODE_PLAY;   // reset selection
            display_menu();
            break;

        case GAME_STATE_PLAY:
            game_init(ctx);
            break;

        case GAME_STATE_HELP:
            displayHelpScreen();
            break;

        case GAME_STATE_GAME_OVER:
            game_over_init(ctx);
            break;
    }
}

 
void game_state_update(GameContext *ctx, uint8_t joystick)
{
    switch (ctx->game_state) {

        case GAME_STATE_MENU:
            menu_update(ctx, joystick);
            break;

        case GAME_STATE_PLAY:
            game_loop(ctx, joystick);
            break;

        case GAME_STATE_HELP:
            help_update(ctx, joystick);
            break;

        case GAME_STATE_GAME_OVER:
            game_over_update(ctx, joystick);
            break;
    }
}


void game_init(GameContext *ctx){
    // initialize game variables here
    ctx->timer_counter = 0;
    ctx->level = 1;
    bullets_set_max(ctx, &bullet_system);
    bullets_init(&bullet_system);
    player_init();   // Initialize player
    game_borders();      // Draw game borders
}

void game_loop(GameContext *ctx, uint8_t joystick){
    ctx->timer_counter++;

    if(ctx->timer_counter > 2700){
        ctx->timer_counter = 1800; // reset to avoid overflow
    }
    if(ctx->timer_counter % 900 == 0){
        // Every 30 seconds (30Hz), increase level
        if(ctx->level < 3){
            ctx->level++;
            bullets_set_max(ctx, &bullet_system); // Update max bullets for new level
            bullets_init(&bullet_system); // Re-initialize bullets
        }
    }

    print_level(ctx);
    print_score(&p);
    print_hp(&p);
   
    score_update(p.highscore, p.score);       // 1. værdig er highscore, 2. værdig er current score (er begger int)
    eraseAlien(&p, ctx);
    update_player(&p, joystick, ctx);
    drawAlien(&p, ctx);

    spawn_powerup(&p, ctx);
    powerups_Update(ctx, &p);
    powerup_effects_update(&p);
    // Update and draw bullets
    erase_bullet(&bullet_system);
    spawn_simple_bullet(&bullet_system);
    update_bullets(ctx, &bullet_system);
    draw_bullets(&bullet_system);
    liv_update(&p);
    led_update(&p);
    // If forcefield is active, apply its repulsion to all bullets before physics update
if (p.forcefield_active) {
    for (int i = 0; i < bullet_system.max_bullets; i++) {
        Bullet *b = &bullet_system.bullets[i];
        if (b->alive) {
            powerup_forcefield_apply(&p, b);
        }
    }
}

    if (p.hp <= 0) {
                    ctx->game_state = GAME_STATE_GAME_OVER;
                    game_state_init(ctx);
                }

}


