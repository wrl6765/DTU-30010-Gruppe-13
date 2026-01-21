#include "Ascii.h"
#include "HAL.h"
#include "bsp/30010_io.h"
#include "bullets.h"
#include <stdlib.h>
#include "help.h"
#include "game_state.h"



void bullets_set_max(GameContext *ctx, BulletSystem *bs)
{
    switch (ctx->level) {
        case 1: bs->max_bullets = 10; break;
        case 2: bs->max_bullets = 15; break;
        case 3: bs->max_bullets = 20; break;
        default: bs->max_bullets = 10; break;
    }
}

// Initialize bullet system
void bullets_init(BulletSystem *bs){
    for(int i = 0; i < bs->max_bullets; i++){
        bs->bullets[i].alive = 0;
        bs->bullets[i].x = 0;
        bs->bullets[i].y = 0;
        bs->bullets[i].vx = 0;
        bs->bullets[i].vy = 0;
        bs->bullets[i].ax = 0;
        bs->bullets[i].ay = 0;
        bs->bullets[i].type = 1;  // Default to type 1 (regular)
    }
}

void spawn_simple_bullet(BulletSystem *bs){
    for(int i=0;i<bs->max_bullets;i++){
        if(!bs->bullets[i].alive){

            Bullet *b = &bs->bullets[i];
            // Spawn from right side of scre    en
            b->x = (DISPLAY_WIDTH - 3) << 8;  // -3 to be inside border
            
            // Random Y position along the right side (inside borders)
            b->y = (2 + rand() % (DISPLAY_HEIGHT - 4)) << 8;
            // Random angle: -30 to +30 degrees (shooting left with some vertical component)
            int angle = (rand() % 61) - 30;  // angle in degrees
            
            // Base leftward velocity (negative x direction)
            // vx should be negative (moving left), scaled by 256 for fixed-point
            b->vx = -128 - (rand() % 128);  // -128 to -255 (slower than before)

            // vy based on angle: negative = up, positive = down
            // Scale proportionally to angle
            b->vy = (b->vx * angle) / 60;  // angle/60 gives ratio

            // 30% chance to spawn type 2 (bouncing), 70% type 1 (regular)
            b->type = (rand() % 10 < 3) ? 2 : 1;  // 1=regular, 2=bouncing

            b->alive = 1;
            break;
        }
    }
}



void erase_bullet(BulletSystem *bs){
    for(int i=0;i<bs->max_bullets;i++){
        if(bs->bullets[i].alive){
            int x = bs->bullets[i].x >> 8;
            int y = bs->bullets[i].y >> 8;
            
            // Erase based on bullet type
            if(bs->bullets[i].type == 3) {
                // Type 3 is 3 lines tall
                for(int line = 0; line < 3; line++) {
                    gotoxy(x, y + line);
                    printf("\033[90m%c%c%c\033[0m", 250, 250, 250);  // 3 spaces for OOO
                }
            } else {
                // Types 1, 2, 4 are 1 line
                gotoxy(x, y);
                if(bs->bullets[i].type == 4) {
                    printf("\033[90m%c%c\033[0m", 250, 250);  // 2 spaces for **
                } else {
                    printf("\033[90m%c%c%c\033[0m", 250, 250, 250);  // 3 spaces for --- or ===
                }
            }
        }
    }
}

void update_bullets(GameContext *ctx, BulletSystem *bs){
    for(int i=0;i<bs->max_bullets;i++){
        if(bs->bullets[i].alive){
            // Update positions
            bs->bullets[i].x += bs->bullets[i].vx;
            bs->bullets[i].y += bs->bullets[i].vy;
            bs->bullets[i].vx += bs->bullets[i].ax;
            bs->bullets[i].vy += bs->bullets[i].ay;

            //-----player bullet collision-----
            if(player_collides_with_bullet(&p, &bs->bullets[i])){
                // Handle collision (e.g., reduce player HP)
                p.hp--;
                
                bs->bullets[i].alive = 0;  // Destroy bullet on hit
                continue;  // Skip further processing for this bullet
            }


            int screen_x = bs->bullets[i].x >> 8;
            int screen_y = bs->bullets[i].y >> 8;

            if(bs->bullets[i].type == 2) {
                // Bouncing bullet - dies at left edge, bounces at other edges
                if(screen_x < 2) {
                    bs->bullets[i].alive = 0;  // Die at left edge
                } else {
                    // die at right edge
                    if(screen_x > (DISPLAY_WIDTH)) {
                        bs->bullets[i].alive = 0;  // Die at right edge
                    }
            
                    // Bounce off top/bottom edges
                    if(screen_y < 2) {
                        bs->bullets[i].vy = -bs->bullets[i].vy;
                        bs->bullets[i].y = 2 << 8;
                    } else if(screen_y > (DISPLAY_HEIGHT - 2)) {
                        bs->bullets[i].vy = -bs->bullets[i].vy;
                        bs->bullets[i].y = (DISPLAY_HEIGHT - 2) << 8;
                    }
                }
            } 
            else {
                // Normal bullet - dies when it goes off the left edge or top/bottom
                int screen_x = bs->bullets[i].x >> 8;
                int screen_y = bs->bullets[i].y >> 8;
                
                if(screen_x < 2 || screen_y < 2 || screen_y > (DISPLAY_HEIGHT - 2))
                    bs->bullets[i].alive = 0;
            }
         
            }
        }
    }




void draw_bullets(BulletSystem *bs){
    for(int i=0;i<bs->max_bullets;i++){
        if(bs->bullets[i].alive){
            gotoxy((int)(bs->bullets[i].x >> 8), (int)(bs->bullets[i].y >> 8));
            // TODO: Replace with your display function
            // For now, using printf for reference
            drawBullet(&bs->bullets[i]);
        }
    }
}