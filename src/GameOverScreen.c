#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdint.h>
#include <stdio.h>

void my_gotoxy(uint8_t x, uint8_t y) {
    printf("\033[%d;%dH", y, x);
}

void displayGameOver(int w, int h, uint32_t score, uint32_t highscore) {  // w=width, h=height
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
            if (py == y + h/4 && px == x + w/2 - 5) {
                printf("GAME OVER");
            }
            if (py == y + h/2 && px == x + w/2 - 7) {
                printf("Score: %lu", score);
            }
            if (py == y + h/2 + 1 && px == x + w/2 - 9) {
                printf("Highscore: %lu", highscore);
            }
            if (py == y + h/2 + 4 && px == x + w/2 - 7) {
                printf("[ GO TO MENU ]"); // placeholder for back to menu
            }
        }
    }
}

int main(void) {
    uart_init(115200);
    printf("\033[2J"); // clear screen

    uint32_t CurrentScore = 12345;
    uint32_t HighScore = 67890;

    displayGameOver(50, 20, CurrentScore, HighScore);

    //---------------------Joystick pressed start--------------------------
    	RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    		GPIOB->MODER &= ~(0x00000003 << (5 * 2));
    		GPIOB->MODER |= (0x00000000 << (5 * 2));
    		GPIOB->PUPDR &= ~(0x00000003 << (5 * 2));
    		GPIOB->PUPDR |= (0x00000002 << (5 * 2));

    	uint8_t val;
    	uint8_t joystick_pressed;
    	//---------------------Joystick pressed end--------------------------
    while(1){
    	//---------------------Joystick pressed start--------------------------
    	val = 0;
    	joystick_pressed = 0;
    	val|= ((GPIOB->IDR & (0x0001 << 5)) ? 1 : 0);//center

    	if (val & (0x1)){ // hvis joystick center button pressed så er joystick_pressed=0x01
    				joystick_pressed |= 0x1;
    			}
    	if (joystick_pressed == 0x1)
    	{
    		// return (something)
    	}
    	//-------------------Joystick presssed end------------------------
    }
}
