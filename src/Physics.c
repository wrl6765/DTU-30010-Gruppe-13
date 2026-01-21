#include "Physics.h"
#include "Ascii.h"
#include "HAL.h"
#include "bullets.h"
#include "game_state.h"
 
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
	p.height=ALIEN_HEIGHT_LVL_1;
	p.width=ALIEN_WIDTH;	
	p.heart.active = 0;
	p.forcefield.active = 1;
	p.multiplier.active = 0;
	p.heart_dir = 1;
	p.forcefield_dir = -1;
}

bool player_collides_with_bullet(const player *p, const Bullet *b){
	// Define player collision box
	int player_left = p->x >> 8;
	int player_right = player_left + p->width;
	int player_top = p->y >> 8;
	int player_bottom = player_top + p->height;

	// Define bullet collision box
	int bullet_left = b->x >> 8;
	int bullet_right = bullet_left + BULLET_WIDTH;
	int bullet_top = b->y >> 8;
	int bullet_bottom = bullet_top + BULLET_HEIGHT;

	// Check for overlap
	if (player_left < bullet_right &&
		player_right > bullet_left &&
		player_top < bullet_bottom &&
		player_bottom > bullet_top) {
		return true;  // Collision detected
	}
	return false;  // No collision
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
	// -----height update-----
	if (ctx->level == 1){
		p->height = ALIEN_HEIGHT_LVL_1;
		p->width = ALIEN_WIDTH;
	}
	if (ctx->level == 2){
		p->height = ALIEN_HEIGHT_LVL_2;
		p->width = ALIEN_WIDTH;
	}
	else if (ctx->level == 3){
		p->height = ALIEN_HEIGHT_LVL_3;
		p->width = ALIEN_WIDTH;
	}
}




