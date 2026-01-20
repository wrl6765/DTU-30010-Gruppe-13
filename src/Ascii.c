#include "Ascii.h"
#include "30010_io.h"
#include "Physics.h"
#include "game_state.h"
#include "bullets.h"

  // grå tegn i baggrunden

void bgcolor(uint8_t background) {

    printf("\x1B[4%dm", background);
}


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
				printf(BG_DOT, 250);  // 250 er en prik
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

// ---------- Saturn drawing ----------
void drawSaturn()
{
    uint16_t saturn_x = 20;  // hard-coded kolonne start
    uint16_t saturn_y = 8;  // hard-coded række start

    // Saturn ASCII sprite
    static const char *saturnSprite[] = {
        "...............................................................................",
        "...............................................................................",
        ".....................:.........................................................",
        "....................:===-:.....................................................",
        "......................-==++==:.................................................",
        "......................-=++++++=:...............................................",
        ".......................:=++-:-=+=-.............................................",
        "........................:=+=:..:-=+*%%@@@%%#+-:................................",
        "..........................-++:..=@@@@@@@@@@@@%#+-..............................",
        "............................:=+=+%@@@@@@@@@@@@@@%#+:...........................",
        "..............................:**#%@@@@@@@@@@@@@@@%*:..........................",
        "..............................=@%###@@@@@@@@@@@@@@@%*:.........................",
        "..............................*@@@%##%@@@@@@@@@@@@@%#=.........................",
        "..............................*@@@@@%*#%@@@@@@@@@@@@%+:........................",
        "..............................-@@@@@@@%##%@@@@@@@@@%%+:........................",
        "...............................*@@@@@@@@#**%@@@@@@@%#=:........................",
        "................................+@@@@@@@@@%**#@@@@%#+:.........................",
        ".................................-%@@@@@@@@@%***#%%+:..........................",
        "..................................:-#@@@@@@@@%#*+=-....::......................",
        ".....................................:-+#%%%%#+=-==-:..:-=-:...................",
        "......................................................:=+=---=+=-..............",
        ".......................................................:-=+++++=-..............",
        "..........................................................:-=++==-............."
    };

    int height = sizeof(saturnSprite) / sizeof(saturnSprite[0]);

    // Saturn med grayscale mapping
    for (int i = 0; i < height; i++) {
        gotoxy(saturn_x, saturn_y + i);
        for (int j = 0; saturnSprite[i][j] != '\0'; j++) {
            char c = saturnSprite[i][j];

            if (c == '.')
                printf(BG_DOT, 250);           // background gray dot
            else if (c == ':' || c == '-')
                printf(BG_DOT, 248);           // slightly brighter
            else if (c == '+' || c == '=')
                printf(BG_DOT, 246);           // medium gray
            else if (c == '*')
                printf(BG_DOT, 244);           // darker gray
            else if (c == '@' || c == '%')
                printf(BG_DOT, 242);           // darkest gray
            else if (c == '#')
                printf(BG_DOT, 243);           // medium-dark gray
            else
                printf(BG_DOT, 250);           // background
        }
    }
}

// ---------- Alien sprite ----------
void drawAlien(player *p, GameContext *ctx)
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

	switch(ctx->level){
	case 1: // level 1
		sprite = level1;
		height = ALIEN_HEIGHT_LVL_1;
		break;
	case 2: // level 2
		sprite = level2;
		height = ALIEN_HEIGHT_LVL_2;
		break;
	case 3: // level 3
		sprite = level3;
		height = ALIEN_HEIGHT_LVL_3;
		break;

	}

	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		printf("%s", sprite[i]);
	}
}

void eraseAlien(player *p, GameContext *ctx)
{
    int height;

    switch(ctx->level){
    case 1: height = ALIEN_HEIGHT_LVL_1; break;
    case 2: height = ALIEN_HEIGHT_LVL_2; break;
    case 3: height = ALIEN_HEIGHT_LVL_3; break;
    default: height = ALIEN_HEIGHT_LVL_1;
    }

    for (int i=0; i<height; i++) {
        gotoxy((p->prev_x)>>8, (p->prev_y>>8)+i);
        for (int j=0; j<ALIEN_WIDTH; j++) {
            printf(BG_DOT, 250);
            
        }
    }
	p->prev_y = p->y;
}

// ---------- Bullet drawing ----------
void drawBullet(Bullet *b)
{
	// x og y position af øvre venstre hjørne af bullet. Bullet tegnes som læst herfra
	uint16_t x = (b->x >> 8);
	uint16_t y = (b->y >> 8);

	int height = 1;

	if (b->type == 3) {
		height = 3;
	}

	for(int i=0; i<height; i++){
		gotoxy(x, y+i);
		switch(b->type){
		case 1: printf("---"); break; //regular
		case 2: printf("==="); break; // bouncing
		case 3: printf("OOO"); break; // cannonball
		case 4: printf("**"); break; // sniper
		}
	}
}

void drawPowerup(Powerup *pu)
{
	// Powerup sprites
	static const char heartSprite[POWERUP_HEIGHT][POWERUP_WIDTH +1] = {
	    " *** ",
	    "*   *",
	    "*<3 *",
	    "*   *",
	    " *** "
	};

	static const char shieldSprite[POWERUP_HEIGHT][POWERUP_WIDTH +1] = {
	    " *** ",
	    "*   *",
	    "*[ ]*",
	    "*   *",
	    " *** "
	};

    if (!pu->active) return;

    uint16_t x = (pu->x >> 8);
    uint16_t y = (pu->y >> 8);

    const char (*sprite)[POWERUP_WIDTH +1];

    switch (pu->type) {
    case POWERUP_HEART:
        sprite = heartSprite;
        break;
    case POWERUP_SHIELD:
        sprite = shieldSprite;
        break;
    default:
        return;
    }

    for (int i=0; i<POWERUP_HEIGHT; i++) {
        gotoxy(x, y+i);
        for (int j = 0; sprite[i][j] != '\0'; j++) {
            char c = sprite[i][j];
            printf("%c", c);
        }
    }
}

void erasePowerup(Powerup *pu)
{
    if (!pu->active) return;

    for (int i=0; i<POWERUP_HEIGHT; i++) {
        gotoxy((pu->prev_x >> 8), (pu->prev_y >> 8) + i);
        for (int j = 0; j < POWERUP_WIDTH; j++) {
            printf(BG_DOT, 250);
        }
    }

    pu->prev_x = pu->x;
    pu->prev_y = pu->y;
}

//--------------print level--------------
void print_level(GameContext *ctx){
	gotoxy(DISPLAY_WIDTH - 15, 1);
	printf("Level: %d", ctx->level);
}

void print_score(player *p){
	gotoxy(2, 1);
	printf("Score: %d  Highscore: %d", p->score, p->highscore);
}
void print_hp(player *p){
	gotoxy(40, 1);
	printf("HP: %d  ", p->hp);
}