#include "30010_io.h"
#include "HAL.h"
#include "Physics.h"
#include "menu.h"
#include "help.h"
#include "Ascii.h"
#include "Ascii.c"


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
                printf("Move up with joystick held down, otherwise fall down.");
            }
            gotoxy(6, 6);{
                printf("Avoid projectiles. Losing all lives ends the game.");
            }
            gotoxy(6, 8);{
                printf("Controls:");
            }
            gotoxy(8, 9);{
                printf("- Hold joystick down: move up");
            }
            gotoxy(8, 10);{
                printf("- Release joystick: move down");
            }
            gotoxy(8, 11);{
                printf("- Press SPACE: pause game");
            }
            gotoxy(6, 13);{
                printf("Controls:");
            }
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
   //     display_menu();
   //     menu_update();
    }
}
