#include "bsp/stm32f30x_conf.h" // STM32 config
#include "bsp/30010_io.h" // Input/output library for this course
#include "HAL.h"
#include "Ascii.h"
#include "Physics.h"
#include "charset.h"
#include "heart.h"
#include <string.h>
#include "menu.h"
#include "game_state.h"
#include "bullets.h"
#include "adc.h"


int main(){
	//-----------inits start------------------
    uart_init(950000); // Baud rate 950000, compiler didnt like it :( 
	printf("\x1b[?25l"); // Hide terminal cursor
    joystick_init();
    joystickdown_init();
    TIM2_Init();
	led_init();
	init_adc();
	clear();
	GameContext ctx = {
    .game_state = GAME_STATE_MENU,
    .menu_mode  = MENU_MODE_PLAY,
	.prev_joystick = 0,
	.timer_counter = 0,
	.level = 1,
	.highscore = 0,
	};
	uint8_t joystick = 0;
	game_state_init(&ctx);
	//inits end
    	while(1){
			joystick = read_joystick();
    		if (tim2_flag){ //30 Hz timer flag, bruges til main time
    						//player movement, bullet movement, etc.

				game_state_update(&ctx, joystick);
				
    			tim2_flag = 0;
    		}
    	}
} 



// score_update(3, 3475);       // 1. værdig er highscore, 2. værdig er current score (er begger int)
// liv_update(4);               // antal liv (1 til 5)