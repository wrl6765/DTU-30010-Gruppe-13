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
        bullets[i].type = 0;  // Default to normal bullet
    }
}

void spawn_simple_bullet(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(!bullets[i].alive){
            int angle = (rand()%60) - 30;  // angle in degrees (-30 to 30)

            bullets[i].x = W;
            bullets[i].y = rand()%H + 1;

            // Use integer velocity based on angle
            bullets[i].vx = -((angle + 90) / 45);  // Simplified velocity calculation
            bullets[i].vy = ((angle) / 30);        // Simplified vertical velocity

            // 30% chance to spawn bouncing bullet, 70% normal
            bullets[i].type = (rand() % 10 < 3) ? 1 : 0;  // 1=bouncing, 0=normal

            bullets[i].alive = 1;
            break;
        }
    }
}



void erase_bullet(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){
            gotoxy((int)bullets[i].x, (int)bullets[i].y);
            printf("  "); // Erase bullet representation
        }
    }
}

void update_bullets(){
    for(int i=0;i<MAX_BULLETS;i++){
        if(bullets[i].alive){

            bullets[i].x += bullets[i].vx;
            bullets[i].y += bullets[i].vy;

            if(bullets[i].type == 1) {
                // Bouncing bullet - reflects at edges
                if(bullets[i].x < 1 || bullets[i].x > W) {
                    bullets[i].vx = -bullets[i].vx;  // Bounce off left/right edges
                }
                if(bullets[i].y < 1 || bullets[i].y > H) {
                    bullets[i].vy = -bullets[i].vy;  // Bounce off top/bottom edges
                }
                // Keep bouncing bullet in bounds
                if(bullets[i].x < 1) bullets[i].x = 1;
                if(bullets[i].x > W) bullets[i].x = W;
                if(bullets[i].y < 1) bullets[i].y = 1;
                if(bullets[i].y > H) bullets[i].y = H;
            } else {
                // Normal bullet - dies at edges
                if(bullets[i].x < 1 || bullets[i].y < 1 || bullets[i].y > H)
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
            printf("oo");
        }
    }
}
