#include "game_state.h"
#include "Ascii.h"
#include "HAL.h"
#include "Physics.h"
#include "menu.h"
#include "help.h"
#include <stdlib.h>


void display_menu(void){
    int w=DISPLAY_WIDTH,h=DISPLAY_HEIGHT;

       borders();
	
        gotoxy(w/2-4,h/4);
        printf("Rum Reje");
        gotoxy(w/2-15,h/2);
        printf("Press JOYSTICK to PLAY level 1");// 
        gotoxy(w/2-2,h/2+2); 
        bgcolor(1);printf("PLAY");bgcolor(9);
        gotoxy(w/2-2,h/2+4); 
        printf("HELP");
        gotoxy(w/2-2,h/2+6);
        printf("QUIT");
         
      }
 

void menu_update(GameContext *ctx, uint8_t joystick)
{
    uint8_t pressed = joystick & ~ctx->prev_joystick;

    /* DOWN pressed once */
    if (pressed & 0x02) {
        ctx->menu_mode = (ctx->menu_mode + 1) % 3;
    }

    /* CENTER pressed once */
    if (pressed & 0x01) {
        if (ctx->menu_mode == MENU_MODE_PLAY) {
            ctx->game_state = GAME_STATE_PLAY;
            game_state_init(ctx);
        }
        else if (ctx->menu_mode == MENU_MODE_HELP) {
            ctx->game_state = GAME_STATE_HELP;
            game_state_init(ctx);
        }
        else if (ctx->menu_mode == MENU_MODE_QUIT) {
            clear();
            gotoxy((DISPLAY_WIDTH >> 1)-7, 16);
            printf("Exiting game...");
            gotoxy(0, 0);
            printf("\x1b[?25h"); // Show terminal cursor
            exit(0);
        }
    }

    ctx->prev_joystick = joystick;

uint8_t h=DISPLAY_HEIGHT; uint8_t w = DISPLAY_WIDTH;

    /* Draw selection */
    if (ctx->menu_mode == MENU_MODE_PLAY && ctx->game_state == GAME_STATE_MENU) {
        printf("\x1B[%d;%dH\033[41mPLAY\033[0m",(h/2)+2,(w/2)-2);
        printf("\x1B[%d;%dHHELP",(h/2)+4,(w/2)-2);
        printf("\x1B[%d;%dHQUIT",(h/2)+6,(w/2)-2);
    }
    else if (ctx->menu_mode == MENU_MODE_HELP && ctx->game_state == GAME_STATE_MENU) {
        printf("\x1B[%d;%dHPLAY",(h/2)+2,(w/2)-2);
        printf("\x1B[%d;%dH\033[41mHELP\033[0m",(h/2)+4,(w/2)-2);
        printf("\x1B[%d;%dHQUIT",(h/2)+6,(w/2)-2);
    }
    else if (ctx->menu_mode == MENU_MODE_QUIT && ctx->game_state == GAME_STATE_MENU) {
        printf("\x1B[%d;%dHPLAY",(h/2)+2,(w/2)-2);
        printf("\x1B[%d;%dHHELP",(h/2)+4,(w/2)-2);
        printf("\x1B[%d;%dH\033[41mQUIT\033[0m",(h/2)+6,(w/2)-2);
    }

  
}