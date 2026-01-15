#include "bsp/30010_io.h"

#define gotoxy(X,Y) printf("\x1B[%d;%dH",(int)(Y),(int)(X))
#define clear() printf("\x1B[2J")
#define hide_cursor() printf("\x1B[?251")

#define DISPLAY_HEIGHT  ((uint16_t)0x20)  // 32
#define DISPLAY_WIDTH   ((uint16_t)0x64)  // 100

#define X_COORDINATE    (DISPLAY_WIDTH << 8)
#define Y_COORDINATE    (DISPLAY_HEIGHT << 8)

// Alien sprite definition
#define ALIEN_WIDTH   (4 << 8)
#define ALIEN_HEIGHT   (3 << 8)

void drawAlien(uint16_t x, uint16_t y);


void borders();