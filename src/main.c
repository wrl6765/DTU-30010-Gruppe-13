#include "stm32f30x_conf.h" // STM32 config
#include "bsp/30010_io.h" // Input/output library for this course
#include "HAL.h"
#include "Ascii.h"
#include "main.h"
#include "Physics.h"


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


