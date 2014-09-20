#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

uint16_t keyboard_isEnter = 0;

unsigned char kbdus[128] =
{
  0,27,'1','2','3','4','5','6','7','8',	/* 9 */
  '9','0','-','=','\b',/* Backspace */
  '\t',	/* Tab */
  'q','w','e','r',/* 19 */
  't','y','u','i','o','p','[',']','\n',/* Enter key */
  0,/* 29   - Control */
  'a','s','d','f','g','h','j','k','l',';',/* 39 */
 '\'','`',90,/* Left shift */
 '\\','z','x','c','v','b','n',/* 49 */
  'm',',','.','/',91,/* Right shift */
  '*',
   0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char upperKbdus[128] =
{
  0,27,'!','@','#','$','%','^','&','&',	/* 9 */
  '(',')','_','+','\b',/* Backspace */
  '\t',	/* Tab */
  'Q','W','E','R',/* 19 */
  'T','Y','U','I','O','P','{','}','\n',/* Enter key */
  0,/* 29   - Control */
  'A','S','D','F','G','H','J','K','L',':',/* 39 */
 '\"','~',90,/* Left shift */
 '|','Z','X','C','V','B','N',/* 49 */
  'M','<','>','?',91,/* Right shift */
  '*',
   0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

size_t isShift = 0;

void keyboard_handler()
{
  char command[20];
  int commandIdx = 0;
	unsigned char scancode;
	//Read from port 60 when handler is called.
	//0x60 is the keyboard key port
	scancode = inportb(0x60);
	//if top bit is set, then key has just been released
	//useful for shifts and control/alt
	if (kbdus[scancode] == 0)
		return;

	if ((scancode & 0x80) != 0 )
	{
		if (scancode == 0xAA || scancode == 0xB6)
		{
			isShift = 0;
			return;
		}
	}
	else
	{
		if (kbdus[scancode] == 91 || kbdus[scancode] == 90)
		{
			isShift = 1;
			return;
		}
		if (isShift != 0)
		{
			terminal_putchar(upperKbdus[scancode]);
      command[commandIdx] = upperKbdus[scancode];
      commandIdx++;
		}
		else
			terminal_putchar(kbdus[scancode]);
      command[commandIdx] = kbdus[scancode];
      commandIdx++;

		if (kbdus[scancode] == '\n')
		{
			runShell(command);
		}
		//key just pressed down
	}
}
