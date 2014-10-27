#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>

void scanf(char* s)
{
  unsigned char c;
  int i = 0;
  while (c != '\n')
  {
    c = keyBuf;
    if (c == '\n')
    {
      keyBuf='\0';
      continue;
    }
    else if (c != '\0')
    {
      s[i] = keyBuf;
      i++;
      terminal_putchar(keyBuf); 
      keyBuf = '\0';
    }
  }
}
