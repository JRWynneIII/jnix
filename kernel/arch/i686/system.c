#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>

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

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

uint32_t inl(unsigned short _port)
{
  uint32_t rv;
  __asm__ __volatile__ ("inl %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

unsigned char inb(unsigned short _port)
{
  unsigned char rv;
  rv = inportb(_port);
  return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void outb(unsigned short _port, unsigned char _data)
{
  outportb(_port,_data);
}

void outl(unsigned short _port, uint32_t _data)
{
  __asm__ __volatile__ ("outl %1, %0" : : "dN" (_port), "a" (_data));
}
