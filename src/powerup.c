#include "Physics.h"
#include "bullets.h"
#include <stdlib.h>
#include <math.h>

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
