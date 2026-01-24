/*
#include "box.h"
#include "30010_io.h"
#include <stdint.h>
#include <string.h>

// --------- Global LCD buffer samme som i heart.c ---------
uint8_t lcd_buffer[512];
static uint8_t lcd_initialized = 0;

void lcd_manager_init(void) {
    if (!lcd_initialized) {
        lcd_init();
        memset(lcd_buffer, 0, sizeof(lcd_buffer));
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

// ----------- 32 rækker x 16 kolonner ---------------------
const uint16_t box_data[32] = { 
    0x1FFF, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 
    0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 
    0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001,
    0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1001, 0x1FFF
};

// ----------------- Clear højre del af lcd -----------------
void clear_right(uint8_t x, uint8_t y, uint8_t *buffer) {
    for (int row = 0; row < 32; row++) {
        for (int col = 8; col < 16; col++) { // Rydder kun højre del hvor level baren er
            uint8_t px = x + col;
            uint8_t py = y + row;

            if (px >= 128 || py >= 32) continue;

            uint16_t index = (py / 8) * 128 + px;
            uint8_t bit = py % 8;

            buffer[index] &= ~(1 << bit); // buffer
        }
    }
}

// -------------- Tegner den tomme boks -----------------
void tom_bar(uint8_t x, uint8_t y, uint8_t *buffer)
{
    clear_right(x, y, buffer); // ryd højre halvdel

    // tegner den tomme boks
    for (int row = 0; row < 32; row++) {
        uint16_t row_data = box_data[row]; // hent data fra fra box_data

        for (int col = 0; col < 16; col++) {
            if (row_data & (1 << (15 - col))) { 
                uint8_t px = x + col; // vandret
                uint8_t py = y + row; // lodret

                if (px >= 128 || py >= 32) continue; //LCD grænser

                uint16_t index = (py / 8) * 128 + px;
                uint8_t bit = py % 8;
                buffer[index] |= (1 << bit); 
            }
        }
    }
}

// ----------------- Fylder time bar per række -----------------
void fill_time_bar(uint8_t x, uint8_t y, uint8_t filled_rows, uint8_t *buffer)
{
    if (filled_rows > 30) filled_rows = 30; // så level 3 forbliver fuld

    for (int row = 0; row < filled_rows; row++) {
        uint8_t py = y + (31 - row); // start fra nederste række

        if (py >= 32) continue;

        for (int col = 8; col < 16; col++) { // højre halvdel
            uint8_t px = x + col;
            if (px >= 128) continue; // LCD grænser

            uint16_t index = (py / 8) * 128 + px;
            uint8_t bit = py % 8;

            buffer[index] |= (1 << bit); // buffer
        }
    }
}

// ----------------- Fylder time bar ift tid -----------------
void box_draw_level_bar(uint8_t x, uint8_t y, uint16_t timer_counter, uint8_t *buffer){
    uint16_t level_time = timer_counter % 900; // går fra 0 til 899 (30 sek ved 30 Hz?)
    uint8_t filled_rows = (level_time * 30) / 900; // en pixel linje per sec

    clear_right(x, y, buffer);           // ryd højre halvdel
    fill_time_bar(x, y, filled_rows, buffer); // fyld bar
}

// -------- den funktion der skal sættet ind i gameloopet ---------------
void final_timer_bar(uint16_t timer_counter, uint8_t x, uint8_t y){
    uint8_t *buffer = lcd_get_buffer();   // hent global buffer

    // Tegn ramme
    tom_bar(x, y, buffer);

    // Tegn time bar
    box_draw_level_bar(x, y, timer_counter, buffer);

    // Push til LCD
    lcd_commit();
}

*/