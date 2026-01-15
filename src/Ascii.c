#include "Ascii.h"
#include "bsp/30010_io.h"
#include "Physics.h"


//--------------game begin borders-------------
void borders(){

	   hide_cursor();
	   clear();
	   gotoxy(1,1);

	printf("%c", 201);
		for(int i=1; i<(DISPLAY_WIDTH-2); i++){
			printf("%c", 205);
		}
		printf("%c", 187);
		printf("\n");

		for (int f=1; f<DISPLAY_HEIGHT-2; f++){
			printf("%c", 186);
			for (int j=1; j<DISPLAY_WIDTH-2;j++){
				printf("%c", ' ');
			}
			printf("%c", 186);
			printf("\n");

		}
		printf("%c", 200);
				for(int i=1; i<(DISPLAY_WIDTH-2); i++){
					printf("%c", 205);
			}
			printf("%c", 188);
}


// ---------- Alien sprite ----------
void drawAlien(uint16_t x, uint16_t y) {
	static const char sprite[(ALIEN_HEIGHT >> 8)][(ALIEN_WIDTH >> 8)] = {
	" (@@)",
	"/||\\",
	"/__\\"
	};

	for (int i = 0; i < (ALIEN_HEIGHT >> 8); i++) {
		gotoxy((x >> 8), (y >> 8)+ i);
		printf("%s", sprite[i]);
	}
}