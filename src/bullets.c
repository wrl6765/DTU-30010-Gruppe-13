#include "Ascii.h"
#include "HAL.h"
#include "bsp/30010_io.h"
#include "bullets.h"
#include <stdlib.h>
#include "help.h"

Bullet bullets[MAX_BULLETS];

// Initialize bullet system
void bullets_init(void){
    for(int i = 0; i < MAX_BULLETS; i++){
        bullets[i].alive = 0;
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].vx = 0;
        bullets[i].vy = 0;
        bullets[i].ax = 0;
        bullets[i].ay = 0;
        bullets[i].type = 1;  // Default to type 1 (regular)
    }
}

void spawn_simple_bullet(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(!bullets[i].alive){
            // Spawn from right side of screen
            bullets[i].x = (DISPLAY_WIDTH - 3) << 8;  // -3 to be inside border
            
            // Random Y position along the right side (inside borders)
            bullets[i].y = (2 + rand() % (DISPLAY_HEIGHT - 4)) << 8;

            // Random angle: -30 to +30 degrees (shooting left with some vertical component)
            int angle = (rand() % 61) - 30;  // angle in degrees
            
            // Base leftward velocity (negative x direction)
            // vx should be negative (moving left), scaled by 256 for fixed-point
            bullets[i].vx = -128 - (rand() % 128);  // -128 to -255 (slower than before)
            
            // vy based on angle: negative = up, positive = down
            // Scale proportionally to angle
            bullets[i].vy = (bullets[i].vx * angle) / 60;  // angle/60 gives ratio

            // 30% chance to spawn type 2 (bouncing), 70% type 1 (regular)
            bullets[i].type = (rand() % 10 < 3) ? 2 : 1;  // 1=regular, 2=bouncing

            bullets[i].alive = 1;
            break;
        }
    }
}



void erase_bullet(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){
            int x = bullets[i].x >> 8;
            int y = bullets[i].y >> 8;
            
            // Erase based on bullet type
            if(bullets[i].type == 3) {
                // Type 3 is 3 lines tall
                for(int line = 0; line < 3; line++) {
                    gotoxy(x, y + line);
                    printf("\033[90m%c%c%c\033[0m", 250, 250, 250);  // 3 spaces for OOO
                }
            } else {
                // Types 1, 2, 4 are 1 line
                gotoxy(x, y);
                if(bullets[i].type == 4) {
                    printf("\033[90m%c%c\033[0m", 250, 250);  // 2 spaces for **
                } else {
                    printf("\033[90m%c%c%c\033[0m", 250, 250, 250);  // 3 spaces for --- or ===
                }
            }
        }
    }
}

void update_bullets(GameContext *ctx){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){
            // Update positions
            bullets[i].x += bullets[i].vx;
            bullets[i].y += bullets[i].vy;
            bullets[i].vx += bullets[i].ax;
            bullets[i].vy += bullets[i].ay;

            //-----player bullet collision-----
            if(player_collides_with_bullet(&p, &bullets[i])){
                // Handle collision (e.g., reduce player HP)
                p.hp--;
                if (p.hp <= 0) {
                    ctx->game_state = GAME_STATE_GAME_OVER;
                    game_state_init(ctx);
                }
                bullets[i].alive = 0;  // Destroy bullet on hit
                continue;  // Skip further processing for this bullet
            }


            int screen_x = bullets[i].x >> 8;
            int screen_y = bullets[i].y >> 8;

            if(bullets[i].type == 2) {
                // Bouncing bullet - dies at left edge, bounces at other edges
                if(screen_x < 2) {
                    bullets[i].alive = 0;  // Die at left edge
                } else {
                    // Bounce off right edge
                    if(screen_x > (DISPLAY_WIDTH - 3)) {
                        bullets[i].vx = -bullets[i].vx;
                        bullets[i].x = (DISPLAY_WIDTH - 3) << 8;
                    }
                    // Bounce off top/bottom edges
                    if(screen_y < 2) {
                        bullets[i].vy = -bullets[i].vy;
                        bullets[i].y = 2 << 8;
                    } else if(screen_y > (DISPLAY_HEIGHT - 2)) {
                        bullets[i].vy = -bullets[i].vy;
                        bullets[i].y = (DISPLAY_HEIGHT - 2) << 8;
                    }
                }
            } 
            else {
                // Normal bullet - dies when it goes off the left edge or top/bottom
                int screen_x = bullets[i].x >> 8;
                int screen_y = bullets[i].y >> 8;
                
                if(screen_x < 2 || screen_y < 2 || screen_y > (DISPLAY_HEIGHT - 2))
                    bullets[i].alive = 0;
            }
         
            }
        }
    }




void draw_bullets(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){
            gotoxy((int)(bullets[i].x >> 8), (int)(bullets[i].y >> 8));
            // TODO: Replace with your display function
            // For now, using printf for reference
            drawBullet(&bullets[i]);
        }
    }
}