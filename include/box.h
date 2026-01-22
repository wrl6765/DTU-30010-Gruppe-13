#ifndef BOX_H
#define BOX_H

#include <stdint.h>

// ---------- Data til boksen (32 rækker x 16 kolonner) ----------
extern const uint16_t box_data[32]; 

// ---------- Funktioner til boks og level bar ----------
void clear_right(uint8_t x, uint8_t y, uint8_t *buffer);                      // rydder højre halvdel
void tom_bar(uint8_t x, uint8_t y, uint8_t *buffer);                          // tegner tom boks
void fill_time_bar(uint8_t x, uint8_t y, uint8_t filled_rows, uint8_t *buffer); // fylder baren per række
void box_draw_level_bar(uint8_t x, uint8_t y, uint16_t timer_counter, uint8_t *buffer); // fylder bar ud fra tid

void final_timer_bar(uint16_t timer_counter, uint8_t x, uint8_t y); // det ENESTE skal i game loopet eller game_state ???

#endif // BOX_H
