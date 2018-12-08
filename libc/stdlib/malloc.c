#include <stdbool.h> 
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

void* malloc(size_t size)
{
	//TODO: Use a heap in userspace. That way the kernel heap is not same as system
	return *kmalloc(size); 
}

