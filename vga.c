#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* Hardware text mode color constants. */
 
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 

uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void movecsr(size_t row, size_t column)
{
	unsigned short temp = (row * 80) + column;
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, temp);

}
 
void backspace()
{
	terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
	terminal_column--;
	movecsr(terminal_row,terminal_column);
		
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + (x-1);
	terminal_buffer[index] = make_vgaentry(c, color);
	movecsr(terminal_row,terminal_column);
}

 
void terminal_scroll(int y)
{
	unsigned short* tbuffer;
	unsigned blank = 0x20 | (0x0F << 8);
        tbuffer	= (unsigned short*)0xB8000;
	unsigned temp = y-25+1;
	memcpy(tbuffer,tbuffer + temp * 80,(25-temp)*80*2);
	memsetw(tbuffer + (25-temp) * 80, blank, 80);
}

void terminal_putchar(char c)
{
	movecsr(terminal_row,terminal_column);
	if (terminal_row >= VGA_HEIGHT)
	{
		terminal_scroll(terminal_row);
		terminal_row = 24;
	}

	if ( c == '\n' )
	{
		terminal_column = 0;
		terminal_row++;
		return;
	}
	if (c == '\b')
	{
		backspace();
		return;
	}
	
	if (++terminal_column >= VGA_WIDTH )
	{
		terminal_column = 0;
		terminal_row++;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
}
 
void tcputs(const char* data, uint8_t color)
{
	uint8_t old_color = terminal_color;
	terminal_color = color;
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
	terminal_color = old_color;
}

void tputs(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}


 
void tprintf(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
	
}

void cls()
{
	unsigned short* tbuffer;
	unsigned blank = 0x20 | (0x0F << 8);
        tbuffer	= (unsigned short*)0xB8000;
	memsetw(tbuffer, blank, 80*25);
	terminal_row = 0;
	terminal_column = 0;
}

char* itoa(int value) 
{
   static char buffer[12];        // 12 bytes is big enough for an INT32
   int original = value;        // save original value
 
   int c = sizeof(buffer)-1;

   buffer[c] = 0;                // write trailing null in last byte of buffer    

   if (value < 0)                 // if it's negative, note that and take the absolute value
       value = -value;
     
   do                             // write least significant digit of value that's left
   {
       buffer[--c] = (value % 10) + '0';    
       value /= 10;
   } while (value);

   if (original < 0) 
       buffer[--c] = '-';

   return &buffer[c];
}

