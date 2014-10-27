#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
//#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}
