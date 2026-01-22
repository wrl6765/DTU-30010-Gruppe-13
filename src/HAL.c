#include "HAL.h"
#include "Physics.h"
#include "game_state.h"
#include "Ascii.h"

// LED pins
#define LED1_PIN   4   // PB4
#define LED2_PIN   7   // PC7

// LED timer max
#define LED_BLINK_DURATION 15  // ticks (~0.5 sec at 30Hz)
//-----------------------------------Joystick stuff start------------------------------------------

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
uint8_t read_joystick(void){
	uint8_t val = 0;
	val |= ((GPIOB->IDR & (0x0001 << 5)) ? 1 : 0); // center
	val |= ((GPIOB->IDR & (0x0001 << 0)) ? 2 : 0); // down
	return val;}
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
	//--------------------------LED stuff start--------------------------------------------
	void led_init(void)
{
    // Enable GPIO clocks
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC;

    // ---- PB4 (LED1) ----
    GPIOB->MODER &= ~(0x3 << (LED1_PIN * 2));  // clear mode
    GPIOB->MODER |=  (0x1 << (LED1_PIN * 2));  // output
    GPIOB->OTYPER &= ~(1 << LED1_PIN);         // push-pull
    GPIOB->OSPEEDR &= ~(0x3 << (LED1_PIN*2));
    GPIOB->OSPEEDR |=  (0x2 << (LED1_PIN*2));  // medium speed

    // ---- PC7 (LED2) ----
    GPIOC->MODER &= ~(0x3 << (LED2_PIN * 2));  // clear mode
    GPIOC->MODER |=  (0x1 << (LED2_PIN * 2));  // output
    GPIOC->OTYPER &= ~(1 << LED2_PIN);         // push-pull
    GPIOC->OSPEEDR &= ~(0x3 << (LED2_PIN*2));
    GPIOC->OSPEEDR |=  (0x2 << (LED2_PIN*2));  // medium speed

    // Turn off LEDs initially
    GPIOB->ODR &= ~(1 << LED1_PIN);
    GPIOC->ODR &= ~(1 << LED2_PIN);
}
	// Set LED states: bit0 = LED1, bit1 = LED2
void set_leds(uint8_t state)
{
    if (state & 0x01)
        GPIOB->ODR |= (1 << LED1_PIN);
    else
        GPIOB->ODR &= ~(1 << LED1_PIN);

    if (state & 0x02)
        GPIOC->ODR |= (1 << LED2_PIN);
    else
        GPIOC->ODR &= ~(1 << LED2_PIN);
}

// Trigger LED blink
void led_trigger(player *p)
{
    p->led_timer = LED_BLINK_DURATION; // reset timer
}

void led_update(player *p)
{
	gotoxy(5,5);
	printf("led_timer: %2d\n", p->led_timer);
    if(p->led_timer > 0){
        set_leds(2);    // LED ON
        p->led_timer--;
    } else {
        set_leds(0);    // LED OFF
    }
}

