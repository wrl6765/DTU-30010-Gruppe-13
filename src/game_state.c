#include "game_state.h"
#include "menu.h"
#include "help.h"
#include "Ascii.h"
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
            game_loop();
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

void game_loop(void){
    // main game loop here
    update_player(&p, joystick_center_pressed());
    drawAlien(&p); 
    
    // Update and draw bullets
    spawn_simple_bullet();
    update_bullets();
    //powerup_repel_bullets(&p);  // Repel bullets on player contact
    draw_bullets();
}

void menu_state_init(void){
    display_menu();
}


void help_state_init(void){
    displayHelpScreen(DISPLAY_WIDTH, DISPLAY_HEIGHT);
}

