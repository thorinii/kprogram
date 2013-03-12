#ifndef _H_KEYBOARD
#define _H_KEYBOARD

#define SCROLL_LED 1
#define NUM_LED 2
#define CAPS_LED 4

#define KEY_PRINT 1
#define KEY_NOPRINT 2

extern void keyboard_lights(char status); // In keyboard.c
extern void setkeyboardhandler(int (*)(char k, int sc));
extern char readkey(int print);
extern int readline(int print, char* buffer);

struct keyhandler{
  int (*handler)(char key, int scancode);
};

#endif