#include "Ascii.h"
#include "HAL.h"
#include "bsp/30010_io.h"
#include "bullets.h"

Bullet bullets[MAX_BULLETS];

// Initialize bullet system
void bullets_init(void){
    for(int i = 0; i < MAX_BULLETS; i++){
        bullets[i].alive = 0;
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].vx = 0;
        bullets[i].vy = 0;
        bullets[i].type = 1;  // Default to type 1 (regular)
    }
}

void spawn_simple_bullet(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(!bullets[i].alive){
            int angle = (rand()%60) - 30;  // angle in degrees (-30 to 30)

            // Use 8.8 fixed-point format (multiply by 256)
            bullets[i].x = (rand()%DISPLAY_WIDTH) << 8;
            bullets[i].y = (rand()%DISPLAY_HEIGHT + 1) << 8;

            // Use lower integer velocity based on angle
            bullets[i].vx = -((angle + 90) / 90);
            bullets[i].vy = ((angle) / 60);

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
            gotoxy((int)bullets[i].x, (int)bullets[i].y);
            
        }
    }
}

void update_bullets(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){

            bullets[i].x += bullets[i].vx;
            bullets[i].y += bullets[i].vy;

            if(bullets[i].type == 2) {
                // Bouncing bullet - reflects at edges
                if(bullets[i].x < (1 << 8) || bullets[i].x > (DISPLAY_WIDTH << 8)) {
                    bullets[i].vx = -bullets[i].vx;  // Bounce off left/right edges
                }
                if(bullets[i].y < (1 << 8) || bullets[i].y > (DISPLAY_HEIGHT << 8)) {
                    bullets[i].vy = -bullets[i].vy;  // Bounce off top/bottom edges
                }
                // Keep bouncing bullet in bounds
                if(bullets[i].x < (1 << 8)) bullets[i].x = (1 << 8);
                if(bullets[i].x > (DISPLAY_WIDTH << 8)) bullets[i].x = (DISPLAY_WIDTH << 8);
                if(bullets[i].y < (1 << 8)) bullets[i].y = (1 << 8);
                if(bullets[i].y > (DISPLAY_HEIGHT << 8)) bullets[i].y = (DISPLAY_HEIGHT << 8);
            } else {
                // Normal bullet - dies at edges
                if(bullets[i].x < (1 << 8) || bullets[i].y < (1 << 8) || bullets[i].y > (DISPLAY_HEIGHT << 8))
                    bullets[i].alive = 0;
            }
        }
    }
}



void draw_bullets(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){
            // TODO: Replace with your display function
            // For now, using printf for reference
            drawBullet(&bullets[i]);
        }
    }
}
