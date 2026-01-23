#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f30x_conf.h"
#include "game_state.h"


// Initialiserer ADC og GPIO
void init_adc(void);

// Læser ADC-værdi (0–4095) fra valgt kanal 8 og 9 (pins CP2 CP3) 
uint16_t read_adc(uint8_t channel);

void read_joystick_adc(GameContext *ctx);

// Læser ADC og printer værdi
void update_display_with_adc(void);

//#define read_joystick_updown()   read_adc(ADC_Channel_8)   // PC2
//#define read_joystick_leftright() read_adc(ADC_Channel_9)  // PC3


#endif /* ADC_H_ */
