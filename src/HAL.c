#include "HAL.h"
//-----------------------------------Joystick stuff start------------------------------------------
// ---------------- Joystick ----------------

void joystick_init(void)
{
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    GPIOB->MODER &= ~(0x3 << (5 * 2));   // PB5 input
    GPIOB->PUPDR &= ~(0x3 << (5 * 2));
    GPIOB->PUPDR |=  (0x2 << (5 * 2));   // pull-down
}

void joystickdown_init(void)
{
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    GPIOB->MODER &= ~(0x3 << (0 * 2));   // PB0 input
    GPIOB->PUPDR &= ~(0x3 << (0 * 2));
    GPIOB->PUPDR |=  (0x2 << (0 * 2));   // pull-down
}

uint8_t joystick_center_pressed(void)
{
    return (GPIOB->IDR & (1 << 5)) ? 1 : 0;
}

uint8_t joystick_down_pressed(void)
{
    return (GPIOB->IDR & (1 << 0)) ? 1 : 0;
}
	//-----------------------------------Joystick stuff end------------------------------------------
	//-----------------------------------timer stuff start------------------------------------------

	volatile uint8_t tim2_flag = 0;
	// TIM2 init: 30 Hz interrupt
	void TIM2_Init(void)
	{
	    RCC->APB1ENR |= 0x00000001; // TIM2 clock enable
	    TIM2->PSC = 6399;           // prescaler
	    TIM2->ARR = 332;            // auto-reload
	    TIM2->CNT = 0x0000;         // clear counter
	    TIM2->DIER = 0x0001;        // enable update interrupt
	    TIM2->CR1 = 0x0001;         // enable timer

	    NVIC->ISER[0] = 0x10000000; // enable TIM2 IRQ
	    NVIC->IP[28] = 0x10;        // priority 1
	}

	// TIM2 interrupt handler
	void TIM2_IRQHandler(void)
	{
	    if (TIM2->SR & 0x0001) // UIF flag
	    {
	        TIM2->SR &= ~0x0001; // clear flag
	        tim2_flag = 1;
	    }
	}



	//-----------------------------------timer stuff end------------------------------------------
