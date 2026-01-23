#include "Ascii.h"
#include "HAL.h"
#include "bsp/30010_io.h"
#include "bullets.h"
#include <stdlib.h>
#include "help.h"
#include "game_state.h"
#include "adc.h"



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

void spawn_simple_bullet(BulletSystem *bs, GameContext *ctx)
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


 
             //Random angle (-30° to +30°)
            int angle = (rand() % 61) - 30;

            // Fixed-point velocity
            if (b->type == BULLET_TYPE_CANNON) {
            b->vx = -96;          // slower than regular
            } else {
            b->vx = -160;
            }
            b->vy = (b->vx * angle) / 60;

            read_joystick_adc(ctx);
            // scale to fixed-point acceleration
            b->ax = (ctx->joy_ax >> 9);   
            b->ay = -1*(ctx->joy_ay >> 10);

        // bullet type scales with level
        switch (ctx->level) {
            case 1:
                b->type = 1; // only regular
                break;
        
            case 2: {
                int r = rand() % 10;
                b->type = (r < 3) ? 2 : 1; // 30% bouncing
                break;
            }
        
            case 3: {
                int r = rand() % 10;
                if (r < 2)
                    b->type = 3;      // 20% cannonball
                else if (r < 5)
                    b->type = 2;      // 30% bouncing
                else
                    b->type = 1;      // 50% regular
                break;
            }
        }


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
            if (bs->bullets[i].type == BULLET_TYPE_CANNON) {
                p.hp -= 2;
            } else {
                p.hp -= 1;
            }



            led_trigger(&p);
            bs->bullets[i].alive = 0;
             // Destroy bullet on hit
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
            else if (bs->bullets[i].type == 1){
                // Normal bullet - dies when it goes off the left edge or top/bottom
                int screen_x = bs->bullets[i].x >> 8;
                int screen_y = bs->bullets[i].y >> 8;
                
                if(screen_x < 2 || screen_y < 2 || screen_y > (DISPLAY_HEIGHT - 2))
                    bs->bullets[i].alive = 0;
            }
            else if(bs->bullets[i].type == 3){
                int screen_x = bs->bullets[i].x >> 8;
                int screen_y = bs->bullets[i].y >> 8;
                
                if(screen_x < 2 || screen_y < 2 || screen_y > (DISPLAY_HEIGHT - 4))
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