#include "Physics.h"
#include "Ascii.h"
#include "HAL.h"
#include "bullets.h"
#include "game_state.h"
#include "stm32f30x_flash.h"
 
//----------------player Physics----------------------
player p; 

void player_init(){
	// movement
	p.x=X_COORDINATE/6;
	p.y=Y_COORDINATE/2;
	p.vy=0;
	p.ay=0;
	p.prev_x=p.x;
	p.prev_y=p.y;

	//general attributes
	p.score=0;
	p.score_multiplier=1;
	p.hp=5;

	//physical attributes
	p.height=ALIEN_HEIGHT_LVL_1;
	p.width=ALIEN_WIDTH;
	
	//powerup effect status
	p.forcefield_active = 0;
	p.multiplier_active = 0;
	p.forcefield_timer = 0;
	p.multiplier_timer = 0;

	//pickup inits
	p.heart_pickup.active = 0;
    p.heart_pickup.x = 0;
    p.heart_pickup.y = 0;
    p.heart_pickup.prev_x = 0;
    p.heart_pickup.prev_y = 0;
    p.heart_pickup.vx = 0;
    p.heart_pickup.vy = 0;
    p.heart_pickup.type = POWERUP_HEART;

	p.forcefield_pickup.active = 0;
    p.forcefield_pickup.x = 0;
    p.forcefield_pickup.y = 0;
    p.forcefield_pickup.prev_x = 0;
    p.forcefield_pickup.prev_y = 0;
    p.forcefield_pickup.vx = 0;
    p.forcefield_pickup.vy = 0;
    p.forcefield_pickup.type = POWERUP_FORCEFIELD;

	p.multiplier_pickup.active = 0;
    p.multiplier_pickup.x = 0;
    p.multiplier_pickup.y = 0;
    p.multiplier_pickup.prev_x = 0;
    p.multiplier_pickup.prev_y = 0;
    p.multiplier_pickup.vx = 0;
    p.multiplier_pickup.vy = 0;
    p.multiplier_pickup.type = POWERUP_MULTIPLIER;

	//led stuff
	p.led_timer = 0;
}

inline int bullet_height(const Bullet *b)
{
    switch (b->type) {
        case 3:  // cannonball
            return BULLET_HEIGHT_CANNON;
        default: // regular, bouncing, sniper, etc.
            return BULLET_HEIGHT_NORMAL;
    }
}


bool player_collides_with_bullet(player *p, const Bullet *b){
	// Define player collision box
	int player_left = p->x >> 8;
	int player_right = player_left + p->width;
	int player_top = p->y >> 8;
	int player_bottom = player_top + p->height;

	// Define bullet collision box
	int bullet_left = b->x >> 8;
	int bullet_right = bullet_left + BULLET_WIDTH;
	int bullet_top = b->y >> 8;
	int bullet_bottom = bullet_top + bullet_height(b);

	// Check for overlap
	if (player_left < bullet_right &&
		player_right > bullet_left &&
		player_top < bullet_bottom &&
		player_bottom > bullet_top) {
		return true;  // Collision detected
	}
	return false;  // No collision
}

bool heal_collides_with_player(player *p) {
	// Define player collision box
	int player_left = p->x >> 8;
	int player_right = player_left + p->width;
	int player_top = p->y >> 8;
	int player_bottom = player_top + p->height;

	// Define heal powerup collision box
	int heal_left = p->heart_pickup.x >> 8;
	int heal_right = heal_left + POWERUP_WIDTH;
	int heal_top = p->heart_pickup.y >> 8;
	int heal_bottom = heal_top + POWERUP_HEIGHT;

	// Check for overlap
	if (player_left < heal_right &&
		player_right > heal_left &&
		player_top < heal_bottom &&
		player_bottom > heal_top) {
		return true;  // Collision detected
	}
	return false;  // No collision
}

bool multiplier_collides_with_player(player *p) {
	// Define player collision box
	int player_left = p->x >> 8;
	int player_right = player_left + p->width;
	int player_top = p->y >> 8;
	int player_bottom = player_top + p->height;

	// Define multiplier powerup collision box
	int mult_left = p->multiplier_pickup.x >> 8;
	int mult_right = mult_left + POWERUP_WIDTH;
	int mult_top = p->multiplier_pickup.y >> 8;
	int mult_bottom = mult_top + POWERUP_HEIGHT;

	// Check for overlap
	if (player_left < mult_right &&
		player_right > mult_left &&
		player_top < mult_bottom &&
		player_bottom > mult_top) {
		return true;  // Collision detected
	}
	return false;  // No collision
}

bool forcefield_collides_with_player(player *p) {
	// Define player collision box
	int player_left = p->x >> 8;
	int player_right = player_left + p->width;
	int player_top = p->y >> 8;
	int player_bottom = player_top + p->height;

	// Define forcefield powerup collision box
	int ff_left = p->forcefield_pickup.x >> 8;
	int ff_right = ff_left + POWERUP_WIDTH;
	int ff_top = p->forcefield_pickup.y >> 8;
	int ff_bottom = ff_top + POWERUP_HEIGHT;

	// Check for overlap
	if (player_left < ff_right &&
		player_right > ff_left &&
		player_top < ff_bottom &&
		player_bottom > ff_top) {
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




/*
void load_bullets() {
    uint32_t magic = *(uint32_t*)SAVE_ADDRESS;
    if (magic == 0x12345678) {
        uint32_t *data = (uint32_t*)&bs;
        int size = sizeof(BulletSystem);
        for(int i = 0; i < size / 4; i++) {
            data[i] = *(uint32_t*)(SAVE_ADDRESS + (i+1) * 4);
        }
    }
}
void save_bullets() {
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
    FLASH_ErasePage(SAVE_ADDRESS);
    FLASH_ProgramWord(SAVE_ADDRESS, 0x12345678); // magic
    uint32_t *data = (uint32_t*)&bs;
    int size = sizeof(BulletSystem);
    for(int i = 0; i < size / 4; i++) {
        FLASH_ProgramWord(SAVE_ADDRESS + (i+1) * 4, data[i]);
    }
    FLASH_Lock();
}
*/

