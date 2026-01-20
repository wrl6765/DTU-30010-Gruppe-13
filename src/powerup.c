#include "Physics.h"
#include "bullets.h"
#include <math.h>
#include "game_state.h"

void powerup_heal_player(player *p) { //should be called when there is collision with heal powerup
    p->hp += 2; // Heal 2 HP
    if (p->hp > 5) {  // Assuming max HP is 5
        p->hp = 5;
    }
}

void powerup_score_multiplier(player *p, GameContext *ctx) { //should be called when there is collision with score multiplier powerup
    uint32_t timer = ctx->timer_counter; 
    p->score_multiplier = 2;  // Double score
    if (timer % 300 == 0)
    {
        p->score_multiplier = 1;  // Reset to normal after 300 ticks
    }

}
// Player repel powerup - repels bullets away in random direction when they contact player
void powerup_repel_bullets(player *p) {
    // Define player collision box (approximate hitbox around player position)
    int player_width = 4;   // Player character width
    int player_height = 3;  // Player character height
    
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i].alive) {
            // Check collision between bullet and player
            if(bullets[i].x >= p->x - player_width && 
               bullets[i].x <= p->x + player_width &&
               bullets[i].y >= p->y - player_height && 
               bullets[i].y <= p->y + player_height) {
                
                // Bullet hit player - repel in random direction
                int random_angle = rand() % 360;  // Random angle 0-359 degrees
                
                // Convert angle to velocity components
                // Using simplified integer math for 8 directions
                int direction = random_angle / 45;  // 0-7 for 8 directions
                
                switch(direction) {
                    case 0:  // Right
                        bullets[i].vx = 2;
                        bullets[i].vy = 0;
                        break;
                    case 1:  // Down-Right
                        bullets[i].vx = 1;
                        bullets[i].vy = 1;
                        break;
                    case 2:  // Down
                        bullets[i].vx = 0;
                        bullets[i].vy = 2;
                        break;
                    case 3:  // Down-Left
                        bullets[i].vx = -1;
                        bullets[i].vy = 1;
                        break;
                    case 4:  // Left
                        bullets[i].vx = -2;
                        bullets[i].vy = 0;
                        break;
                    case 5:  // Up-Left
                        bullets[i].vx = -1;
                        bullets[i].vy = -1;
                        break;
                    case 6:  // Up
                        bullets[i].vx = 0;
                        bullets[i].vy = -2;
                        break;
                    case 7:  // Up-Right
                        bullets[i].vx = 1;
                        bullets[i].vy = -1;
                        break;
                    default:
                        bullets[i].vx = 2;
                        bullets[i].vy = 0;
                }
                
                // Move bullet away from player to avoid multiple collisions
                bullets[i].x = p->x + (bullets[i].vx * 2);
                bullets[i].y = p->y + (bullets[i].vy * 2);
            }
        }
    }
}

// Updates powerups using random test powerups
// Bevæger sig vandret og bouncer af vægge (hvis vi vil bruge denne funktion)
void powerupsUpdate(GameContext *ctx, Powerup *heart, Powerup *shield, int *heart_dir, int *shield_dir) {
    // Only do anything if the game is in play mode
    if (ctx->game_state != GAME_STATE_PLAY) return;

    // Initialize powerups if they are inactive (test values)
    if (!heart->active) {
        heart->x = 10 << 8;
        heart->y = 5 << 8;
        heart->prev_x = heart->x;
        heart->prev_y = heart->y;
        heart->type = POWERUP_HEART;
        heart->active = 1;
    }

    if (!shield->active) {
        shield->x = 50 << 8;
        shield->y = 12 << 8;
        shield->prev_x = shield->x;
        shield->prev_y = shield->y;
        shield->type = POWERUP_SHIELD;
        shield->active = 1;
    }

    // --- Erase old powerups ---
    erasePowerup(heart);
    erasePowerup(shield);

    // --- Move powerups horizontally ---
    heart->x += (*heart_dir) << 8;
    shield->x += (*shield_dir) << 8;

    // --- Bounce off screen edges ---
    if ((heart->x >> 8) <= 1 || (heart->x >> 8) >= DISPLAY_WIDTH - POWERUP_WIDTH)
        *heart_dir *= -1;

    if ((shield->x >> 8) <= 1 || (shield->x >> 8) >= DISPLAY_WIDTH - POWERUP_WIDTH)
        *shield_dir *= -1;

    // --- Draw updated powerups ---
    drawPowerup(heart);
    drawPowerup(shield);
}

/*
Dette kan bruges senere i main loopet

// Define powerups and directions
Powerup heart = {.active = 0};
Powerup shield = {.active = 0};
int heart_dir = 1;
int shield_dir = -1;

// In your main loop (inside tim2_flag)
testPowerupsUpdate(&ctx, &heart, &shield, &heart_dir, &shield_dir);

*/
