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


int main(){
	//-----------inits------------------
    uart_init(1000000);
	printf("\x1b[?25l"); // Hide terminal cursor
    joystick_init();
    joystickdown_init();
    TIM2_Init();
	clear();
	GameContext ctx = {
    .game_state = GAME_STATE_MENU,
    .menu_mode  = MENU_MODE_PLAY,
	.prev_joystick = 0,
	.timer_counter = 0,
	.level = 1,
	.highscore = 0
};

	uint8_t joystick = 0;
	// uint8_t game_state = GAME_STATE_MENU; // 0=menu, 1=game, 2=help
	// uint8_t menuMode = MENU_MODE_HELP; // 0=play, 1=help, 2=quit
	// uint8_t *menu_mode = &menuMode;
	game_state_init(&ctx);
    	while(1){
//
			joystick = read_joystick();
//
    		if (tim2_flag){ //30 Hz timer flag, bruges til main time
    //						//player movement, bullet movement, osv.

				game_state_update(&ctx, joystick);
				
    			tim2_flag = 0;
    		}
    	}
} 



// score_update(3, 3475);       // 1. værdig er highscore, 2. værdig er current score (er begger int)
// liv_update(4);               // antal liv (1 til 5)



