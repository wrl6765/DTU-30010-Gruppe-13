#include "Physics.h"
#include "Ascii.h"
#include "HAL.h"
 
//----------------player Physics----------------------
player p; 

void player_init(){
	p.x=X_COORDINATE/6;
	p.y=Y_COORDINATE/2;
	p.vy=0;
	p.ay=0;
	p.score=0;
	p.score_multiplier=1;
	p.hp=5;
	p.prev_x=p.x;
	p.prev_y=p.y;
}

void update_player(player* p, uint8_t joystick, GameContext *ctx){
// -----movement physics-----
	if (joystick & 0x01){
		p->ay = -16; //op
	}
	else if (!(joystick == 0x01)){
		p->ay = 8; //gravity
	}
	// -----score update-----
	p->score += p->score_multiplier;
	
    if (p->score > p->highscore) {
        p->highscore = p->score;
    }
	// -----position update-----
	p->vy += p->ay;
	p->y += p->vy;

	// -----boundary conditions-----
	switch (ctx->level)
	{
	case 1:
		/* code */
	if (p->y < Y_MIN + 256){
		p->y = Y_MIN + 256;
		p->vy = 0;
		
	}
	else if (p->y > Y_MAX - ((ALIEN_HEIGHT_LVL_1 - 1) << 8)){
		p->y = Y_MAX - ((ALIEN_HEIGHT_LVL_1 - 1) << 8);
		p->vy = 0;
	}
		break;
	case 2:
	if (p->y < Y_MIN + 256){
		p->y = Y_MIN + 256;
		p->vy = 0;
	}
	else if (p->y > Y_MAX - ((ALIEN_HEIGHT_LVL_2 - 1) << 8)){
		p->y = Y_MAX - ((ALIEN_HEIGHT_LVL_2 - 1) << 8);
		p->vy = 0;
	}
		break;
	case 3:
	if (p->y < Y_MIN + 256){
		p->y = Y_MIN + 256;
		p->vy = 0;
	}
	else if (p->y > Y_MAX - ((ALIEN_HEIGHT_LVL_3 - 1) << 8)){
		p->y = Y_MAX - ((ALIEN_HEIGHT_LVL_3 - 1) << 8);
		p->vy = 0;
	}
		break;
	}
	
}




