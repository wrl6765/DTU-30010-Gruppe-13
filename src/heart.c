#include "heart.h"
#include "bsp/30010_io.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// ---------------- LCD manager -----------------
uint8_t lcd_buffer[512];
static uint8_t lcd_initialized = 0;

void lcd_manager_init(void) {
    if (!lcd_initialized) {
        lcd_init();
        memset(lcd_buffer, 0x00, 512);
        lcd_initialized = 1;
    }
}

uint8_t *lcd_get_buffer(void) {
    lcd_manager_init();
    return lcd_buffer;
}

void lcd_commit(void) {
    lcd_push_buffer(lcd_buffer);
}
// ------------ Hjerte Full: 16 kolonner x 13 rækker ------------------
const uint16_t full_heart_data[13] = {
    0x1E3C, 0x3F7E, 0x7FFF, 0x7FFF,
    0x7FFF, 0x7FFF, 0x3FFE, 0x1FFC,
    0x0FF8, 0x07F0, 0x03E0, 0x01C0,
    0x0080
};

// ------------- Hjerte Tom: 16 kolonner x 13 rækker ------------------
const uint16_t tom_heart_data[13] = {
    0x1E3C, 0x2142, 0x4081, 0x4001,
    0x4001, 0x4001, 0x2002, 0x1004,
    0x0808, 0x0410, 0x0220, 0x0140,
    0x0080
};

// --------------- Tegn fyldt hjerte -------------------------------
void heart_full(uint8_t x, uint8_t y, uint8_t *buffer) {
    for (int row = 0; row < 13; row++) {
        uint16_t row_data = full_heart_data[row];

        for (int col = 0; col < 16; col++) {
            if (row_data & (1 << (15 - col))) {
                uint8_t pixel_x = x + col;
                uint8_t pixel_y = y + row;

                if (pixel_x >= 128 || pixel_y >= 32) continue;

                uint16_t byte_index = (pixel_y / 8) * 128 + pixel_x;
                uint8_t bit = pixel_y % 8;

                buffer[byte_index] |= (1 << bit);
            }
        }
    }
}

// ------------------ Tegn tomt hjerte ---------------------------
void heart_tom(uint8_t x, uint8_t y, uint8_t *buffer) {
    for (int row = 0; row < 13; row++) {
        uint16_t row_data = tom_heart_data[row];

        for (int col = 0; col < 16; col++) {
            if (row_data & (1 << (15 - col))) {
                uint8_t pixel_x = x + col;
                uint8_t pixel_y = y + row;

                if (pixel_x >= 128 || pixel_y >= 32) continue;

                uint16_t byte_index = (pixel_y / 8) * 128 + pixel_x;
                uint8_t bit = pixel_y % 8;

                buffer[byte_index] |= (1 << bit);
            }
        }
    }
}


// ------------ Koordinater for de 5 hjerter (y = lodret, x = vandret) -------------- 
static const uint8_t heart_x[5] = {16, 36, 56, 76, 96}; // vandret med 20 pixels mellemrum
static const uint8_t heart_y[5] = {19, 19, 19, 19, 19}; // lodret samme linje

// ------------- display for de 5 hjærter ---------------------------------------------
void display_lives(uint8_t lives, uint8_t *buffer) {
    if (lives > 5) lives = 5; // begræns til max 5

    for (int i = 0; i < 5; i++) {
        if (i < lives) {
            heart_full(heart_x[i], heart_y[i], buffer); // fyldt hjerte
        } else {
            heart_tom(heart_x[i], heart_y[i], buffer);  // tomt hjerte
        }
    }
}

