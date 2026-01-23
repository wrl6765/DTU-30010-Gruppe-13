#include "adc.h"
#include <stdio.h>
#include "game_state.h"
#include "Ascii.h"
#include "30010_io.h"
#include "HAL.h"

// ------------------- aktivere ure / kalibrere ADC -------------
void init_adc(void) {
    // Aktiver clock til Port C og ADC12
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_ADC12;

    // 2. Konfigurer PC2 og PC3 som analog (ADC)
    GPIOC->MODER &= ~((0x3 << (2 * 2)) | (0x3 << (3 * 2)));
    GPIOC->MODER |=  ((0x3 << (2 * 2)) | (0x3 << (3 * 2)));
    
    // Ingen pull-up/pull-down
    GPIOC->PUPDR &= ~((0x0 << (2 * 2)) | (0x0 << (3 * 2)));

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6

    ADC1->CR = 0x00000000; // Clear CR register
    ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
    ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

    ADC1->CR |= 0x10000000; // Enable internal voltage regulator
    for (int i = 0; i < 1000; i++); // Wait for about 16 microseconds
    
    ADC1->CR |= 0x80000000; // Start ADC1 calibration
    while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
    for (int i = 0; i < 100; i++); // Wait for a little while


    ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable
    
	
    while (!(ADC1->ISR & 0x00000001)); // Wait until ready
    


}

// ----------- returnere en værdi mellem 0 og 4095 --------------
uint16_t read_adc(uint8_t abs) {
    ADC_RegularChannelConfig(ADC1, abs, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1); // Start ADC read

    uint32_t timeout = 100000;
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0){
        if (--timeout == 0)
        return 20000;
    } // Wait for ADC read

    return ADC_GetConversionValue(ADC1);
}

void read_joystick_adc(GameContext *ctx)
{
    static uint8_t channel = 0;

    if (channel == 0) {
        ctx->joy_y = ((int)read_adc(0x08) - 2048);
        channel = 1;
        ctx->joy_ay = ctx->joy_y;
    } else {
        ctx->joy_x = ((int)read_adc(0x09) - 2048);
        channel = 0;
        ctx->joy_ax = ctx->joy_x;
    }
}


// -------------- print for potentiometer ----------------------
void update_display_with_adc(void) {
    uint16_t readjoyupdown = read_adc(ADC_Channel_8); //Read the ADC value fra PC2
    uint16_t readjoyleftright = read_adc(ADC_Channel_9); //Read the ADC value fra PC3

    gotoxy(10,10);
    printf("Pot1: %04d | Pot2: %04d\n", readjoyupdown, readjoyleftright);
}
