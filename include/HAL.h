#ifndef HAL_H
#define HAL_H

#include "bsp/stm32f30x.h"
#include "bsp/30010_io.h"

// Joystick
void joystick_init(void);
void joystickdown_init(void);
uint8_t joystick_center_pressed(void);
uint8_t joystick_down_pressed(void);
uint8_t read_joystick(void);

// Timer
void TIM2_Init(void);
void TIM2_IRQHandler(void);

// Global timer flag
extern volatile uint8_t tim2_flag;

#endif
