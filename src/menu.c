/*#include <stdio.h>
#include <stdint.h>
#include "escape.h"
#include <termios.h>
#include <unistd.h>


void set_raw_mode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO); // Turn off line buffering and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    } 

void bgcolor(uint8_t bg){
    printf("\033[%dm",bg+40);
}

//void readjoystick(){
//
//}


void displaymenu(int w,int h){

    int y=1,x=1;
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
    int in;
    int mode = 0;
    set_raw_mode();

    while(1){
        if (read(0, &in,1)==1){
        if (in == 'c' && mode == 0){
            printf("\x1b[%d;%dH",(h/2)+2,(w/2)-2);
            printf("PLAY");
            printf("\x1b[%d;%dH",(h/2)+4,(w/2)-2);
            bgcolor(1);
            printf("HELP");
            bgcolor(9);
            mode = 1;
            }
        if (in == 'c' && mode == 1){
            printf("\x1b[%d;%dH",(h/2)+4,(w/2)-2);
            printf("HELP");
            printf("\x1b[%d;%dH",(h/2)+6,(w/2)-2);
            bgcolor(1);
            printf("QUIT");
            bgcolor(9);
            mode = 2;
        }
        if (in == 'c' && mode == 2){
            printf("\x1b[%d;%dH",(h/2)+6,(w/2)-2);
            printf("QUIT");
            printf("\x1b[%d;%dH",(h/2)+2,(w/2)-2);
            bgcolor(1);
            printf("PLAY");
            bgcolor(9);
            mode = 0;
        }
    }
        
    }
    


}

int main(){
    printf("\x1B[2J");
    displaymenu(90, 25);
    return 0;
}
*/