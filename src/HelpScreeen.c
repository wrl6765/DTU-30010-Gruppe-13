#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdint.h>
#include <stdio.h>
#include "HAL.h"
#include "Physics.h"
#include "menu.h"

void my_gotoxy(uint8_t x, uint8_t y) {
    printf("\033[%d;%dH", y, x);
}

void displayHelpScreen(int w, int h) {  // w=width, h=height
    int x = 3, y = 3;  // start position for boks (øvre venstre hjørne koordinat)

    for (int py = y; py <= y + h; py++) {
        for (int px = x; px <= x + w; px++) {
            my_gotoxy(px, py);

            // hjørner
            if ((px == x && py == y) || (px == x + w && py == y) ||
                (px == x && py == y + h) || (px == x + w && py == y + h)) {
                printf("+");
            }
            // lodrette linjer
            else if (px == x || px == x + w) {
                printf("|");
            }
            // vandrette linjer
            else if (py == y || py == y + h) {
                printf("-");
            }

            // tekst positioner
            if (py == y + 2 && px == x + 3) {
                printf("HELP - How to play");
            }
            if (py == y + 4 && px == x + 3) {
                printf("Explore a mysterious planet in an endless runner.");
            }
            if (py == y + 5 && px == x + 3) {
                printf("Move up with joystick held down, otherwise fall down.");
            }
            if (py == y + 6 && px == x + 3) {
                printf("Avoid projectiles. Losing all lives ends the game.");
            }
            if (py == y + 8 && px == x + 3) {
                printf("Controls:");
            }
            if (py == y + 9 && px == x + 5) {
                printf("- Hold joystick down: move up");
            }
            if (py == y + 10 && px == x + 5) {
                printf("- Release joystick: move down");
            }
            if (py == y + 11 && px == x + 5) {
                printf("- Press SPACE: pause game");
            }
            if (py == y + h - 2 && px == x + w/2 - 7) {
                printf("\x1b[41m");
                printf("[ GO TO MENU ]");
                printf("\x1b[40m");
            }
        }
    }
}

void help_update(void) {
    if (joystick_center_pressed() == 0x1) {
        display_menu();
        menu_update();
    }
}
