#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif
 
void kernel_main()
{
	terminal_initialize();
	tcputs("Initilizing VGA Driver....\n\n",COLOR_WHITE);
	tcputs("Installing Global Descriptor Table....\n\n",COLOR_WHITE);
	gdt_install();
	tcputs("Installing Interrupt Descriptor Table....\n\n",COLOR_WHITE);
	idt_install();
	tcputs("Setting up ISRs...\n\n",COLOR_WHITE);
	isrs_install();
	tcputs("Remapping the PIC and setting up IRQs...\n\n",COLOR_WHITE);
	install_irq();
	tcputs("Starting shell....\n\n\n",COLOR_WHITE);
	init_shell();

	for (;;);
}
