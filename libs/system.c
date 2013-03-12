#include <system.h>
#include <screen.h>

void *memcpy(void *dest, const void *src, size_t count)
{
  const char *sp = (const char *)src;
  char *dp = (char *)dest;
  for(; count != 0; count--) *dp++ = *sp++;
  return dest;
}

void *memset(void *dest, char val, size_t count)
{
  char *temp = (char *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
  unsigned short *temp = (unsigned short *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

size_t strlen(const char *str)
{
  size_t retval;
  for(retval = 0; *str != '\0'; str++) retval++;
  return retval;
}

int strcomp(char* one, char* two){
  char *ptr1 = one;
  char *ptr2 = two;
  int onelen = strlen(one);
  int twolen = strlen(two);
  
  if(onelen != twolen) return FALSE;
  
  for(int i = 0; i < onelen; i++){
    if(*ptr1 != *ptr2) return FALSE;
    ptr1++;
    ptr2++;
  }
  return TRUE;
}

unsigned char inportb (unsigned short _port)
{
  unsigned char rv;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

char intlookuptable[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void printLong(long toprint){
  char tmp[15];
  int curdigit = 0;
  long current = toprint;
  long digit = 0;
  while(TRUE){
    digit = current % 10; // Base 10
    current = current / 10; // Base 10
    
    tmp[curdigit++] = intlookuptable[digit];
    if(current == 0 || curdigit >= 15)
      break;    
  }
  for(; curdigit >= 0; curdigit--){
    putch(tmp[curdigit]);
  }
}
void printLongHex(long toprint){
  char tmp[15];
  int curdigit = 0;
  long current = toprint;
  long digit = 0;
  while(TRUE){
    digit = current % 16; // Base 16
    current = current / 16; // Base 16
    
    tmp[curdigit++] = intlookuptable[digit];
    if(current == 0 || curdigit >= 15)
      break;    
  }
  puts("0x");
  for(; curdigit >= 0; curdigit--){
    putch(tmp[curdigit]);
  }
}


void printLongBin(long toprint){
  char tmp[15];
  int curdigit = 0;
  long current = toprint;
  long digit = 0;
  while(TRUE){
    digit = current % 2; // Base 2
    current = current / 2; // Base 2
    
    tmp[curdigit++] = intlookuptable[digit];
    if(current == 0 || curdigit >= 15)
      break;    
  }
  puts("0b");
  for(; curdigit >= 0; curdigit--){
    putch(tmp[curdigit]);
  }
}

void restart(){
  unsigned char good = 0x02;
  while ((good & 0x02) != 0)
    good = inportb(0x64);
  outportb(0x64, 0xFE);
  while(TRUE)
    __asm__("hlt");
}