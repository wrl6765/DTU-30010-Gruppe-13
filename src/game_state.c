#include "Game_state.h"
#include "menu.h"
#include "help.h"
#include "Ascii.h"
#include "HAL.h"
#include "bullets.h"
#include "powerup.h"

void game_state_init(GameContext *ctx)
{
    clear();

    switch (ctx->game_state) {

        case GAME_STATE_MENU:
            ctx->menu_mode = MENU_MODE_PLAY;   // reset selection
            display_menu();
            break;

        case GAME_STATE_PLAY:
            game_init();
            break;

        case GAME_STATE_HELP:
            displayHelpScreen(DISPLAY_WIDTH, DISPLAY_HEIGHT);
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
            game_loop(ctx);
            break;

        case GAME_STATE_HELP:
            help_update(ctx, joystick);
            break;
    }
}


void game_init(void){
    // initialize game variables here
    bullets_init();      // Initialize bullet system
    player_init();
    borders();

}

void game_loop(GameContext *ctx){
    ctx->timer_counter++;

    if(ctx->timer_counter > 2700){
        ctx->timer_counter = 1800; // reset to avoid overflow
    }
    if(ctx->timer_counter % 900 == 0){
        // Every 30 seconds (assuming 30Hz), increase level
        if(ctx->level < 3){
            ctx->level++;
        }
    }

    print_level(ctx);
    drawAlien(&p, ctx);
    update_player(&p, joystick_center_pressed());
<<<<<<< HEAD
    drawAlien(&p); 

    // Update and draw bullets
    spawn_simple_bullet();
    update_bullets();
    erase_bullet();
=======
    
    
    // Update and draw bullets
    //spawn_simple_bullet();
    //update_bullets();
>>>>>>> 0b88d00693e8890aaeb8b016030d2f6d7081dd3a
    //powerup_repel_bullets(&p);  // Repel bullets on player contact
    //draw_bullets();
}

void menu_state_init(void){
    display_menu();
}


void help_state_init(void){
    displayHelpScreen(DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

