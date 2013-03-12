#ifndef _H_SCREEN
#define _H_SCREEN

// Define colors

#define SCREEN_COLOR_BLACK 0
#define SCREEN_COLOR_BLUE 1
#define SCREEN_COLOR_GREEN 2
#define SCREEN_COLOR_CYAN 3
#define SCREEN_COLOR_RED 4
#define SCREEN_COLOR_MAGENTA 5
#define SCREEN_COLOR_BROWN 6
#define SCREEN_COLOR_LIGHT_GREY 7
#define SCREEN_COLOR_DARK_GREY 8
#define SCREEN_COLOR_LIGHT_BLUE 9
#define SCREEN_COLOR_LIGHT_GREEN 10
#define SCREEN_COLOR_LIGHT_CYAN 11
#define SCREEN_COLOR_LIGHT_RED 12
#define SCREEN_COLOR_LIGHT_MAGENTA 13
#define SCREEN_COLOR_LIGHT_BROWN 14
#define SCREEN_COLOR_WHITE 15

#define BOLD 7

#define SCREEN_X_MAX 80
#define SCREEN_Y_MAX 25

// Define external references to screen routines

extern void puts(char *s);
extern void putch(char c);
extern void putch_loc(char c, int x, int y);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void cls();
extern void resetscr();
extern void boldscr();
extern void errorscr();

#endif