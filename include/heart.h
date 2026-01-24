#ifndef HEART_H
#define HEART_H

#include <stdint.h>
#include "Physics.h"

// Tegn et fyldt hjerte: 16 kolonner x 13 rækker
void heart_full(uint8_t x, uint8_t y, uint8_t *buffer);

// Tegn et tomt hjerte: 16 kolonner x 13 rækker
void heart_tom(uint8_t x, uint8_t y, uint8_t *buffer);

// Lives display 0 til 5
void display_lives(player *p, uint8_t *buffer);

// Opdatere lives
void liv_update(player *p);

uint8_t *lcd_get_buffer(void);

#endif /* _HEART_H_ */