#include "game_state.h"
#include "menu.h"
#include "help.h"
#include "Ascii.h"
#include "HAL.h"
#include "bullets.h"
#include "powerup.h"
#include "Physics.h"
#include "charset.h"
#include "heart.h"

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
    bullets_init();      // Initialize bullet system
    player_init();   // Initialize player
    borders();
    ctx->timer_counter = 0;
    ctx->level = 1;

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
        }
    }

    print_level(ctx);
    print_score(&p);
    print_hp(&p);
   
    score_update(p.highscore, p.score);       // 1. værdig er highscore, 2. værdig er current score (er begger int)
    eraseAlien(&p, ctx);
    update_player(&p, joystick, ctx);
    drawAlien(&p, ctx);
                 // antal liv (1 til 5)
    // Update and draw bullets
    spawn_simple_bullet();
    erase_bullet();
    // If forcefield is active, apply its repulsion to all bullets before physics update
    if (ctx->forcefield_active) {
        for (int i = 0; i < MAX_BULLETS; ++i) {
            if (bullets[i].alive) {
                powerup_forcefield(&p, &bullets[i], ctx);
            }
        }
    }
    update_bullets(ctx);
    draw_bullets();
    liv_update(&p);

}


