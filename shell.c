#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
#include "include/keyboard.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

void init_shell()
{
	tcputs("$>> ", COLOR_GREEN);
	irq_install_handler(1, keyboard_handler);
	//doesn't work because init_shell() will return as soon as it passes this if branch
}

void runShell()
{
	tcputs("$>> ", COLOR_GREEN);
}
