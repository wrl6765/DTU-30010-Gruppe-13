#include "bsp/30010_io.h"
#include "HAL.h"
#include "Physics.h"
#include "menu.h"
#include "help.h"
#include "Ascii.h"
#include "game_state.h"
#include "charset.h"
#include <stdio.h>
#include "pause.h"


void displayHelpScreen() {
 
           borders();
            // Tegn kanter

            gotoxy(6, 3);{
                printf("HELP - How to play");
            }
            gotoxy(6, 4);{
                printf("Explore a mysterious planet in an endless runner.");
            }
            gotoxy(6, 5);{
                printf("Move up with button held down, otherwise fall down.");
            }
            gotoxy(6, 6);{
                printf("An opposing player can control the initial acceleration of bullets.");
            }
            gotoxy(6, 7);{
                printf("Avoid projectiles. Losing all lives ends the game.");
            }
            gotoxy(6, 9);{
                printf("Controls:");
            }
            gotoxy(8, 10);{
                printf("- Press the non-analog joystick: accelerate upwards");
            }
            gotoxy(8, 11);{
                printf("- Release the non-analog joystick: accelerate downwards");
            }
            gotoxy(8, 12);{
                printf("- Press 'M': pause game");
            }
            gotoxy(8, 13);{
                printf("- Use the analog joystick to control bullet acceleration");
            }
            gotoxy(6, 15);{
                printf("Bullets:");
            }
            gotoxy(8,16); {
                printf("- Regular bullets: damage: -1 HP");
            }
            gotoxy(8,17); {
                printf("- Bouncing bullets: damage: -1 HP");
            }
            gotoxy(8,18);{
                printf("- Cannonball bullets: damage: -2 HP");
            }


            gotoxy(6, 20);{
                printf("Power-ups:");
            }
            gotoxy(8,21); {printf("- Heart: +1 HP");}
            gotoxy(8,22); {printf("- Forcefield: Accelerate bullets away from the alien for 10s");}
            gotoxy(8,23); {printf("- Multiplier: Gain 2X points for 10s");}

            
            gotoxy((DISPLAY_WIDTH >> 1) - 7, DISPLAY_HEIGHT - 2);{
                printf("\x1b[41m");
                printf("[ GO TO MENU ]");
                printf("\x1b[40m");
            }
            gotoxy((DISPLAY_WIDTH >> 1) - 21, DISPLAY_HEIGHT - 4);{
                printf("Press CENTER joystick to return to menu.");
            }

        }
    



void help_update(GameContext *ctx, uint8_t joystick) {
    if (ctx->game_state == GAME_STATE_HELP) {
        uint8_t pressed = joystick & ~ctx->prev_joystick;

        /* CENTER pressed once */
        if (pressed & 0x01) {
            ctx->game_state = GAME_STATE_MENU;
            game_state_init(ctx);
        }

        ctx->prev_joystick = joystick;

    }
}

void game_over_init(GameContext *ctx){
        clear();
        borders();
        gotoxy(50-5,16);{printf("GAME OVER");}
        gotoxy(50-8,18);{printf("your score: %d", p.score);}

        gotoxy((DISPLAY_WIDTH >> 1) - 7, DISPLAY_HEIGHT - 2);{
                   printf("\x1b[41m");
                   printf("[ GO TO MENU ]");
                   printf("\x1b[40m");
               }
               gotoxy((DISPLAY_WIDTH >> 1) - 21, DISPLAY_HEIGHT - 4);{
                   printf("Press CENTER joystick to return to menu.");
               }
        }
    
    

void game_over_update(GameContext *ctx, uint8_t joystick) {
    if (ctx->game_state == GAME_STATE_GAME_OVER) {
        uint8_t pressed = joystick & ~ctx->prev_joystick;

        /* CENTER pressed once */
        if (pressed & 0x01) {
            ctx->game_state = GAME_STATE_MENU;
            game_state_init(ctx);
        }

        ctx->prev_joystick = joystick;

    }
}

void pause_init(GameContext *ctx){
    clear();
    game_borders();
    gotoxy((DISPLAY_WIDTH >> 1) - 3,DISPLAY_HEIGHT >> 1);{printf("PAUSED");}
    gotoxy((DISPLAY_WIDTH >> 1) - 10, DISPLAY_HEIGHT - 4);{
        printf("\x1b[41m");
        printf("[ PRESS B TO RESUME ]");
    }
        gotoxy((DISPLAY_WIDTH >> 1) - 10, DISPLAY_HEIGHT - 2);{
            printf("[ PRESS M TO MENU ]");
        printf("\x1b[40m");
    }
    
}

void pause_update(GameContext *ctx) {
    int ch = uart_get_char();
    if (ch == -1) return;
    
    if (ch == 'b' || ch == 'B') {
        ctx->game_state = GAME_STATE_PLAY;
            gotoxy((DISPLAY_WIDTH >> 1) - 3,DISPLAY_HEIGHT >> 1);
                for (int i; i<6; i++){
        printf(BG_DOT, 250);
        }
    gotoxy((DISPLAY_WIDTH >> 1) - 10, DISPLAY_HEIGHT - 4);
        for (int i; i<21; i++){
        printf(BG_DOT, 250);
        }
    
        gotoxy((DISPLAY_WIDTH >> 1) - 10, DISPLAY_HEIGHT - 2);
        for (int i; i<19; i++){
        printf(BG_DOT, 250);
        }
    }

     else if (ch == 'm' || ch == 'M') {
        ctx->game_state = GAME_STATE_MENU;
        game_state_init(ctx);
    }
}



void pause_check(GameContext *ctx)
{
    int ch = uart_get_char();   // NON-blocking

    if (ch == -1)
        return;                // no input = keep running

    if (ctx->game_state == GAME_STATE_PLAY &&
        (ch == 'b' || ch == 'B'))
    {
        ctx->game_state = GAME_STATE_PAUSE;
        game_state_init(ctx);
    
    }
}
