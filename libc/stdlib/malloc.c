#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

unsigned char* mallocBase = (unsigned char*)0x01000000;
unsigned char* mallocTop = (unsigned char*)0xBFFFFFFF;
unsigned char* freeBottom = (unsigned char*)0x01000000;

void* malloc(size_t size)
{
  //this increments the bottom of the freespace by 'size' bytes. Because a char is a byte
  freeBottom = freeBottom + size;
  if (freeBottom >= mallocTop)
    return 0;
  return (freeBottom - size); 
}

