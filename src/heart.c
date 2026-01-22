#include "heart.h"
#include "bsp/30010_io.h"
#include <stdint.h>
#include <string.h>
#include "Physics.h"

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

// ------------ Koordinater for de 5 hjerter -------------------------
const uint8_t heart_x[5] = {10, 30, 50, 70, 90};
const uint8_t heart_y[5] = {19, 19, 19, 19, 19};

// --------------- Slet hjerte område -------------------------------
void heart_clear(uint8_t x, uint8_t y, uint8_t *buffer) {
    for (int row = 0; row < 13; row++) {
        for (int col = 0; col < 16; col++) {

            uint8_t px = x + col;
            uint8_t py = y + row;
            if (px >= 128 || py >= 32) continue;

            uint16_t index = (py / 8) * 128 + px;
            buffer[index] &= ~(1 << (py % 8));
        }
    }
}

// --------------- Tegn fyldt hjerte -------------------------------
void heart_full(uint8_t x, uint8_t y, uint8_t *buffer) {
    heart_clear(x, y, buffer);

    for (int row = 0; row < 13; row++) {
        uint16_t data = full_heart_data[row];

        for (int col = 0; col < 16; col++) {
            if (data & (1 << (15 - col))) {

                uint8_t px = x + col;
                uint8_t py = y + row;
                if (px >= 128 || py >= 32) continue;

                uint16_t index = (py / 8) * 128 + px;
                buffer[index] |= (1 << (py % 8));
            }
        }
    }
}

// ------------------ Tegn tomt hjerte ---------------------------
void heart_tom(uint8_t x, uint8_t y, uint8_t *buffer) {
    heart_clear(x, y, buffer);

    for (int row = 0; row < 13; row++) {
        uint16_t data = tom_heart_data[row];

        for (int col = 0; col < 16; col++) {
            if (data & (1 << (15 - col))) {

                uint8_t px = x + col;
                uint8_t py = y + row;
                if (px >= 128 || py >= 32) continue;

                uint16_t index = (py / 8) * 128 + px;
                buffer[index] |= (1 << (py % 8));
            }
        }
    }
}

// ------------- display for de 5 hjerter --------------------------
void display_lives(player *p, uint8_t *buffer) {
    if (p->hp > 5) p->hp = 5;

    for (int i = 0; i < 5; i++) {
        if (i < p->hp) {
            heart_full(heart_x[i], heart_y[i], buffer);
        } else {
            heart_tom(heart_x[i], heart_y[i], buffer);
        }
    }
}

// ------------ opdater liv (samme stil som score_update) ----------
void liv_update(player *p) {
    uint8_t *buffer = lcd_get_buffer();

    display_lives(p, buffer);
    lcd_commit();
}
