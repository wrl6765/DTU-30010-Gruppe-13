#include "Ascii.h"
#include "30010_io.h"
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

		for (int f=1; f<DISPLAY_HEIGHT-2; f++){
			gotoxy(1, f+1);
			printf("%c", 186);
			for (int j=1; j<DISPLAY_WIDTH-2;j++){
				printf(" ");
			}
			printf("%c", 186);
		}

		gotoxy(1, DISPLAY_HEIGHT-1);
		printf("%c", 200);
				for(int i=1; i<(DISPLAY_WIDTH-2); i++){
					printf("%c", 205);
			}
			printf("%c", 188);
}


// ---------- Alien sprite ----------
void drawAlien(player *p)
{
	uint16_t x = (p->x >> 8);
	uint16_t y = (p->y >> 8);

// Sprite bestemmes afhængigt af level
	static const char level1[ALIEN_HEIGHT_LVL_1][ALIEN_WIDTH +1] = {
	"<@@>",
	"/||\\",
	"/__\\"
	};

	static const char level2[ALIEN_HEIGHT_LVL_2][ALIEN_WIDTH +1] = {
	"<@@>",
	"/||\\",
	"/__\\",
	" /\\ "
	};

	static const char level3[ALIEN_HEIGHT_LVL_3][ALIEN_WIDTH +1] = {
	"<@@>",
	"/||\\",
	"/__\\",
	" /\\ ",
	" || "
	};

	const char (*sprite)[ALIEN_WIDTH +1];
	int height;

	switch(p->alien_level){
	case 2:
		sprite = level2;
		height = ALIEN_HEIGHT_LVL_2;
		break;
	case 3:
		sprite = level3;
		height = ALIEN_HEIGHT_LVL_3;
		break;
	default:
		sprite = level1;
		height = ALIEN_HEIGHT_LVL_1;
		break;
	}

	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		printf("%s", sprite[i]);
	}
}

// ---------- Bullet drawing ----------
void drawBullet(bullet *b)
{
	uint16_t x = (b->x >> 8);
	uint16_t y = (b->y >> 8);

	int w, h;

	switch(b->size){
	case 1: // small
		w = BULLET_SMALL_WIDTH;
		h = BULLET_SMALL_HEIGHT;
		break;
	case 2: // medium
		w = BULLET_MEDIUM_WIDTH;
		h = BULLET_MEDIUM_HEIGHT;
		break;
	case 3: // large
		w = BULLET_LARGE_WIDTH;
		h = BULLET_LARGE_HEIGHT;
		break;
	default:
		w = BULLET_MEDIUM_WIDTH;
		h = BULLET_MEDIUM_HEIGHT;
		break;
	}

	for(int i=0; i<h; i++){
		gotoxy(x, y+i);
		switch(b->type){
		case 1: printf("---"); break; //regular
		case 2: printf("==="); break; // bouncing
		case 3: printf("#####"); break; // cannonball
		case 4: printf("*"); break; // sniper
		}
	}
}
