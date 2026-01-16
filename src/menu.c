
#include "Ascii.h"
#include "HAL.h"
#include "Physics.h"
#include "menu.h"
#include "help.h"


void display_menu(void){

    int y=1,x=1;
    int w=DISPLAY_WIDTH,h=DISPLAY_HEIGHT;

    for (int py = y ; py<y+h ; py++){
        for (int px = x ; px<x+w ; px++){
        gotoxy(px, py);
        if (px == x && py ==y || px == w && py == y || px == w && py == h || px == x && py == h){
              printf("%c",'+');
        }
        else if (py < y+h && px == x || py < y+h && px == w){        
            printf("%c",'|');
        }
        else if (px < x+w && py == y){
            printf("%c",'-');
        }
        else if (py == h){
            printf("%c",'-');
        }
        if (py == h/4 && px == (w/2)-4) printf("Rum Reje");
        if (py == h/2 && px == (w/2)-15) printf("Press JOYSTICK to PLAY level 1");// 
        if (py == (h/2)+2 && px == (w/2)-2) {bgcolor(1);printf("PLAY");bgcolor(9);}// 
        if (py == (h/2)+4 && px == (w/2)-2) {printf("HELP");}// 
        if (py == (h/2)+6 && px == (w/2)-2) {printf("QUIT");}// 
         
      }
    }
}

    
 

void menu_update(void){
    int menu_mode = 0;
    if (joystick_down_pressed == 0x1){
        if(mode == 0) printf("\x1b[%d;%dHPLAY",(h/2)+2,(w/2)-2);

        else if(mode == 1) printf("\x1b[%d;%dHHELP",(h/2)+4,(w/2)-2);

        else printf("\x1b[%d;%dHQUIT",(h/2)+6,(w/2)-2);
        // update mode

        mode = (mode + 1) % 3; // move up cyclically (0→2)
        
        // highlight new
        if(mode == 0) printf("\x1b[%d;%dH\033[41mPLAY\033[0m",(h/2)+2,(w/2)-2);

        else if(mode == 1) printf("\x1b[%d;%dH\033[41mHELP\033[0m",(h/2)+4,(w/2)-2);

        else printf("\x1b[%d;%dH\033[41mQUIT\033[0m",(h/2)+6,(w/2)-2);
    }

    
    if (joystick_center_pressed == 0x1){
        if(mode == 0){
            player_init();
            update_player(&p);
        }
        else if(mode == 1){
            displayHelpScreen(100, 32);
            help_update();
        }
        else{
            // quit program
            clear();
            gotoxy(1,1);
            printf("Quitting program...\n");
            exit(0);
        }
    }
}
