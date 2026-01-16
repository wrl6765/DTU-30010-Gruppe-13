#include "bsp/stm32f30x_conf.h" // STM32 config
#include "bsp/30010_io.h" // Input/output library for this course
#include "HAL.h"
#include "Ascii.h"
#include "Physics.h"
#include "charset.h"
#include "heart.h"
#include <string.h>


int main(){
	//-----------inits------------------
    uart_init(1000000);
    joystick_init();
    joystickdown_init();
    TIM2_Init();
	player_init();
    //---------ikke-loop-Ascii------------------
    borders();

	uint8_t joystick;
    	while(1){

			//joystick variable
		joystick |= joystick_center_pressed();
		joystick |= joystick_down_pressed() << 1;
		

    		if (tim2_flag){ //30 Hz timer flag, bruges til main time
    						//player movement, bullet movement, osv.
					update_player(&p, joystick);
					drawAlien(&p);
    			tim2_flag = 0;
    			}
    	}
}



// score_update(3, 3475);       // 1. værdig er highscore, 2. værdig er current score (er begger int)
// liv_update(4);               // antal liv (1 til 5)



