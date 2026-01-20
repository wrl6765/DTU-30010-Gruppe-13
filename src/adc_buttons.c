
// ------------------- activere ure / kalibrere ADC -------------
void init_adc(void) {
    // 1. Aktiver clock til Port A og ADC12
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_ADC12;

    // 2. Konfigurer PA6 og PA7 som input
    GPIOA->MODER &= ~((0x3 << (6 * 2)) | (0x3 << (7 * 2)));

    // 3. ADC prescaler: divider med 6
    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6;

    // 4. Reset ADC konfiguration
    ADC1->CR = 0x00000000;
    ADC1->CFGR &= 0xFDFFC007;
    ADC1->SQR1 &= ~ADC_SQR1_L;

    // 5. Kalibrering
    ADC1->CR |= 0x10000000; // Enable internal voltage regulator
    for (int i = 0; i < 1000; i++);

    ADC1->CR |= 0x80000000; // Start kalibrering
    while (ADC1->CR & 0x80000000);
    for (int i = 0; i < 100; i++);

    // 6. Aktiver ADC
    ADC1->CR |= 0x00000001;
    while (!(ADC1->ISR & 0x00000001));
}


// ----------- returnere en værdi mellem 0 og 4095 --------------
uint16_t read_adc(uint8_t channel) {
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
    return ADC_GetConversionValue(ADC1);
}


// -------------- print for potentiometer ----------------------
void update_display_with_adc(void) {
    uint16_t pot1 = read_adc(ADC_Channel_10); //Read the ADC value fra  PA6
    uint16_t pot2 = read_adc(ADC_Channel_15); //Read the ADC value fra  PA7

    printf("Pot1: %04d | Pot2: %04d\n", pot1, pot2);
}
