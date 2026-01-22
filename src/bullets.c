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

void spawn_simple_bullet(BulletSystem *bs)
{
    int alive_count = 0;

    // Count alive bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bs->bullets[i].alive)
            alive_count++;
    }

    // Respect max bullets for current level
    if (alive_count >= bs->max_bullets)
        return;

    // Find ONE free slot and spawn ONE bullet
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bs->bullets[i].alive) {
            Bullet *b = &bs->bullets[i];

            b->alive = 1;

            // Spawn position (right side)
            b->x = (DISPLAY_WIDTH - 3) << 8;
            b->y = (2 + rand() % (DISPLAY_HEIGHT - 4)) << 8;

            // Random angle (-30° to +30°)
            int angle = (rand() % 61) - 30;

            // Fixed-point velocity
            b->vx = -160;
            b->vy = (b->vx * angle) / 60;

            b->ax = 0;
            b->ay = 0;

            // Bullet type
            b->type = (rand() % 10 < 3) ? 2 : 1;

            break; // IMPORTANT: only spawn one bullet
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
                led_trigger(&p);
                
                bs->bullets[i].alive = 0;  // Destroy bullet on hit
                continue;  // Skip further processing for this bullet
            }
            // if bullet collides with cannonball, -2 hp
            if(bs->bullets[i].type == 3 && player_collides_with_bullet(&p, &bs->bullets[i])){
                p.hp -= 2;
                led_trigger(&p);
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
            // cannonball -2 p.hp
            else if(bs->bullets[i].type == 3) {
                // Cannonball - dies when off left edge or bottom
                if(screen_x < 2 || screen_y > (DISPLAY_HEIGHT - 2))
                    bs->bullets[i].alive = 0;
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
            drawBullet(&bs->bullets[i]);
        }
    }
}