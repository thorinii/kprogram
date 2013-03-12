#ifndef _H_SYSTEM
#define _H_SYSTEM

#include <config.h>

// Debug call:
#ifdef DEBUG_ON
#define DEBUG(text) puts("\nDebug {"); boldscr(); puts(text); boldscr(); puts("} ");
#else
#define DEBUG(text) ;
#endif

#define TRUE 1
#define FALSE 0
#define NULL 0

#define DOPACKED __attribute__((packed))

typedef int size_t;

extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern int strcomp(char* one, char* two);

extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

extern void printLong(long toprint);
extern void printLongHex(long toprint);
extern void printLongBin(long toprint);

extern int syscall(int intnumber, int sysnumber, int eax, int ebx, int ecx, int edx);

extern void restart();

extern int tickcount();

#endif