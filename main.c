#include <system.h>
#include <screen.h>
#include <keyboard.h>
#include <time.h>

struct command {
  char *cmd;
  char *description;
  void (*func)(int argcount, char *args[]);
};

#define COMMAND_COUNT 5
struct command commands[COMMAND_COUNT];

void cmdloop();
void cmd_forloop(int argcount, char *args[]);
void cmd_divbyzero(int argcount, char *args[]);
void cmd_restart(int argcount, char *args[]);
void cmd_sleep(int argcount, char *args[]);
extern void cmd_pong(int argcount, char * args[]);

void kmain(){
  // Initialize commands
  commands[0].cmd = "for";
  commands[0].description = "Run a for loop";
  commands[0].func = cmd_forloop;
  
  commands[1].cmd = "divide";
  commands[1].description = "Divide a number by zero";
  commands[1].func = cmd_divbyzero;
  
  commands[2].cmd = "restart";
  commands[2].description = "Restart the computer";
  commands[2].func = cmd_restart;
  
  commands[3].cmd = "sleep";
  commands[3].description = "Sleep for 3 seconds";
  commands[3].func = cmd_sleep;
  
  commands[4].cmd = "pong";
  commands[4].description = "Play pong";
  commands[4].func = cmd_pong;
  
  cmdloop();
  // hlt coming...
}

void cmdloop(){
  char buffer[200];
  memcpy(buffer, "game", 5);
  
  puts("\nHi. Welcome to ");
  boldscr();
  puts("K");
  boldscr();
  puts("Program.\n");
  
  while(TRUE){
    memset(buffer, 0, 200);
    puts("You may choose from:\n");
    for(int i = 0; i < COMMAND_COUNT; i++){
      boldscr();
      puts(commands[i].cmd);
      boldscr();
      puts(" - ");
      puts(commands[i].description);
      puts("\n");
    }
    puts("\n> ");
    readline(KEY_PRINT, buffer);
    puts(buffer);
    puts("\n");

    int cmdfound = FALSE;
    for(int i = 0; i < COMMAND_COUNT; i++){
      if(strcomp(buffer, commands[i].cmd)){
	commands[i].func(0, (char )NULL);
	cmdfound = TRUE;
	break;
      }
    }
    if(!cmdfound) puts("What?\n");
  }
}

void cmd_forloop(int argcount, char *args[]){
  puts("Begin forloop...");
  for(int i = 0; i < 100000000; i++){
  }
  puts("done.\n");
}
void cmd_divbyzero(int argcount, char *args[]){
  puts("Begin divbyzero...");
  puts(50/0);
  puts("done.\n");
}
void cmd_restart(int argcount, char *args[]){
  restart();
}
void cmd_sleep(int argcount, char *args[]){
  for(int i = 0; i < 3; i++){
    printLong(i);
    puts("/3");
    sleep(1000);
    puts("\r");
  }
}
