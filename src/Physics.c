#include "Physics.h"
#include "Ascii.h"
#include "HAL.h"
 
//----------------player Physics----------------------
player p; 

void player_init(void){
	p.x=X_COORDINATE/6;
	p.y=Y_COORDINATE/2;
	p.vy=0;
	p.ay=0;
	p.score=0;
	p.hp=5;
}

void update_player(player *p, uint8_t joystick, GameContext *ctx){
	if (joystick & 0x01){
		p->ay = -16; //op
	}
	else if (!(joystick == 0x01)){
		p->ay = 8; //gravity
	}
	p->score+=1;
	p->vy += p->ay;
	p->y += p->vy;

	switch (ctx->level)
	{
	case 1:
		/* code */
		if (p->y < Y_MIN + 256){
		p->y = Y_MIN + 256;
		p->vy = 0;
		break;
	}
	else if (p->y > Y_MAX - (ALIEN_HEIGHT_LVL_1 + 1) << 8){
		p->y = Y_MAX - (ALIEN_HEIGHT_LVL_1 + 1) << 8;
		p->vy = 0;
	}
		break;
	case 2:
	if (p->y < Y_MIN + 256){
		p->y = Y_MIN + 256;
		p->vy = 0;
	}
	else if (p->y > Y_MAX - (ALIEN_HEIGHT_LVL_2 + 1) << 8){
		p->y = Y_MAX - (ALIEN_HEIGHT_LVL_2 + 1) << 8;
		p->vy = 0;
	}
	case 3:
	if (p->y < Y_MIN + 256){
		p->y = Y_MIN + 256;
		p->vy = 0;
	}
	else if (p->y > Y_MAX - (ALIEN_HEIGHT_LVL_3 + 1) << 8){
		p->y = Y_MAX - (ALIEN_HEIGHT_LVL_3 + 1) << 8;
		p->vy = 0;
	}
		break;
	}
	
}




