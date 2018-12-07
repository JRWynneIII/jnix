#include <stdio.h>

#if defined(__is_jnix_kernel)
#include <kernel/tty.h>
#endif

int putchar(int ic)
{
#if defined(__is_jnix_kernel)
  char c = (char)ic;
  terminal_write(&c,sizeof(c));
#else
  //TODO: implement system wrtie call
#endif
  return ic;
}
