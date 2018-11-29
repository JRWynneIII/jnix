#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

unsigned char* mallocBase = (unsigned char*)0x01000000;
unsigned char* mallocTop = (unsigned char*)0xBFFFFFFF;
unsigned char* freeBottom = (unsigned char*)0x01000000;

void* allocate_bytes(size_t size)
{
  //this increments the bottom of the freespace by 'size' bytes. Because a char is a byte
  freeBottom = freeBottom + size;
  if (freeBottom >= mallocTop)
    return 0;
  return (freeBottom - size); 
}

