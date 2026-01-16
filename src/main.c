#include "stm32f30x_conf.h" // STM32 config
#include "bsp/30010_io.h" // Input/output library for this course
#include "HAL.h"
#include "Ascii.h"
#include "main.h"
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
    	while(1){

			//joystick variable
		uint8_t joystick_pressed = joystick_center_pressed();
		uint8_t joystickdown_pressed = joystick_down_pressed();

    		if (tim2_flag){ //30 Hz timer flag, bruges til main time
    						//player movement, bullet movement, osv.

    			tim2_flag = 0;


    			}
    	}
}



// score_update(3, 3475);       // 1. værdig er highscore, 2. værdig er current score (er begger int)
// liv_update(4);               // antal liv (1 til 5)



