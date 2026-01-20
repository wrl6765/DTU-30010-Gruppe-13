#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f30x_conf.h"

// Initialiserer ADC og GPIO
void init_adcbuttons(void);

// Læser ADC-værdi (0–4095) fra valgt kanal (1 eller 2)
uint16_t read_adcbuttons(uint8_t channel);

// Læser ADC og printer værdi
void update_display_with_adcbuttons(void);

#endif /* ADC_H_ */
