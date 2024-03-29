#include <system.h>
#include <screen.h>
#include <boot.h>
#include <time.h>

volatile int timer_ticks = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires.*/
void timer_handler(struct regs *r)
{
  /* Increment our 'tick count' */
  timer_ticks++;
  
  /* Every 100 clocks (approximately 1 second), we will
  *  display a message on the screen */
  //  if (timer_ticks % 100 == 0)
  //  {
    //    DEBUG("One second has passed");
    //  }
}

void timer_phase(int hz)
{
  int divisor = 1193180 / hz;       /* Calculate our divisor */
  outportb(0x43, 0x36);             /* Set our command byte 0x36 */
  outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
  outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
  timer_phase(TIMER_HZ);
  /* Installs 'timer_handler' to IRQ0 */
  irq_install_handler(0, timer_handler);
}

int tickcount(){
  return timer_ticks;
}

void sleep(int milliseconds){
  #ifdef START_PIT
  int endticks = tickcount() + milliseconds; // 1 tick is a millisecond
  while(tickcount() != endticks){
    __asm__("hlt");
  }
  #endif
}