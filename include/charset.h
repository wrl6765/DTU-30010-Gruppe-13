#ifndef _CHARSET_H_
#define _CHARSET_H_

#include <stdint.h>
#include "bsp/30010_io.h"

extern const char character_data[95][5];

// ------------ skriver text på lcd ------------------------
void lcd_write_string(char *str, uint8_t slice, uint8_t line, uint8_t *buffer);

// ------------ skriver specifikt ift palyers status --------
void lcd_text(int a, int b, uint8_t *buffer);

// ------------ opdaterer palyers status --------
void score_update(int high, int score);

#endif /*! _CHARSET_H_ */

