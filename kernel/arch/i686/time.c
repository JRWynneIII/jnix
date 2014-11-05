#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>
#include <stdio.h>

#define NMI_DISABLE 1
#define NMI_ENABLE 0
#define CMOS_0 0x70
#define CMOS_1 0x71

/*  To select a CMOS register:
 *  outb(0x70,NMI_DISABLE << 7 | CMOS_REGISTER_NUMBER);
 *  to read or write new value to register use port 0x71
 *  uint8_t val = inb(0x71);
 *  etc.
 *
 *  wait for a bit after selecting register so CMOS can catch up
 *  
 *  RTC Registers:
 *  Register  Contents
 *  0x00      Seconds
 *  0x02      Minutes
 *  0x04      Hours
 *  0x06      Weekday
 *  0x07      Day of Month
 *  0x08      Month
 *  0x09      Year
 *  0x32      Century (maybe)
 *  0x0A      Status Register A
 *  0x0B      Status Register B
 *  
 *  Check bit 7 of 0x0A. If set then its updating  
 *
 */


uint8_t checkStatus()
{
  outb(0x70,NMI_ENABLE<<7|0x0A);
  uint8_t rtcUpdateStatus = inb(0x71);
  if ((rtcUpdateStatus & 0x80) != 0)
    return true;
  else
    return false; 
}

int8_t getSeconds()
{
//retry:
  while(!checkStatus())
  {}
  outb(0x70,NMI_ENABLE<<7|0x00);
  int8_t sec = inb(0x71);
  //if (sec >=60)
    //goto retry;
  return sec;
}

int8_t getMinutes()
{
  while(!checkStatus())
  {}
  outb(0x70,NMI_ENABLE<<7|0x02);
  int8_t min = inb(0x71);
  return min; 
}

int8_t getHours()
{
  while(!checkStatus())
  {}
  outb(0x70,NMI_ENABLE<<7|0x04);
  int8_t hour = inb(0x71);
  hour -= 5;
  if (hour < 0)
    hour = 12 + hour;
  return hour;
}

void printPrettyTime()
{
  tcputs(itoa(getHours()),COLOR_WHITE);
  tcputs(":",COLOR_WHITE);
  tcputs(itoa(getMinutes()),COLOR_WHITE);
  tcputs(":",COLOR_WHITE);
  tcputs(itoa(getSeconds()),COLOR_WHITE);
  tputs("\n");
}
