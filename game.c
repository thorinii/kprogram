#include <system.h>
#include <screen.h>
#include <keyboard.h>
#include <time.h>

#define PONG_PADDLE_HEIGHT 3
#define USER_PADDLE_COLOR SCREEN_COLOR_GREEN
#define AI_PADDLE_COLOR SCREEN_COLOR_RED
#define BALL_COLOR SCREEN_COLOR_BLUE

int ball_x = 40, ball_y = 12;
int usr_paddle_x = 0, usr_paddle_y = 4;
int ai_paddle_x = 79, ai_paddle_y = 7;

void drawpaddle(int x, int y, int color){
  settextcolor(SCREEN_COLOR_BLACK, color);
  for(int i = 0; i < PONG_PADDLE_HEIGHT; i++){
    putch_loc(' ', x, y + i);
  }
  settextcolor(SCREEN_COLOR_LIGHT_GREY, SCREEN_COLOR_BLACK);
}
void drawball(int x, int y, int color){
  settextcolor(color, SCREEN_COLOR_BLACK);
  putch_loc('o', x, y);
  settextcolor(SCREEN_COLOR_LIGHT_GREY, SCREEN_COLOR_BLACK);  
}
void draw(){
  settextcolor(SCREEN_COLOR_LIGHT_GREY, SCREEN_COLOR_BLACK);
  cls();
  
  drawpaddle(usr_paddle_x, usr_paddle_y, USER_PADDLE_COLOR);
  drawpaddle(ai_paddle_x, ai_paddle_y, AI_PADDLE_COLOR);
  
  drawball(ball_x, ball_y, BALL_COLOR);
}
void update(){
}

void cmd_pong(int argcount, char * args[]){
  while(TRUE){ // The loop
    draw();
    sleep(50);
  }
}