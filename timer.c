#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

volatile int timer_ticks = 0;

void timer_handler()
{
  timer_ticks++;
//  tputs("Got tick");
}

void set_Interval(int hertz)
{
  int divisor = 1193180/hertz;
  outportb(0x43,0x36);
  outportb(0x40,divisor & 0xFF);
  outportb(0x40,divisor >> 8);
}

void timer_install()
{
  set_Interval(100);
  irq_install_handler(0,timer_handler);
}

void wait(int ticks)
{
  //one tick is one millisecond
  //TODO: WHEN WAIT IS CALLED IT SEEMS LIKE TIMER_TICKS ISN'T UPDATED
  unsigned long eticks;
  eticks = timer_ticks + ticks;
  while (timer_ticks < eticks);
}
