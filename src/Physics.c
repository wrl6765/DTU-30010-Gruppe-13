#include "Physics.h"
#include "Ascii.h"

//----------------player Physics----------------------
player p; 

void player_init(void){
	p.x=X_COORDINATE/5;
	p.y=Y_COORDINATE/2;
	p.vy=0;
	p.ay=0;
	p.score=0;
	p.hp=5;
}

void update_player(player *p){
	uint8_t joystick_pressed = joystick_center_pressed();
	if (joystick_pressed == 0x1 && p->y > Y_MIN){
		p->ay = -512; //op
	}
	else if (joystick_pressed == 0x0 && p->y < Y_MAX){
		p->ay = 256; //ned
	}
	p->score+=1;
	p->vy += p->ay;
	p->y += p->vy;	
}




