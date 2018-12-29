#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>
#include <kernel/pci.h>
#include <kernel/ata.h>
#include <kernel/cpuid.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif
 
void kernel_main()
{
	terminal_initialize();
	kprintf("Identifying CPU...", COLOR_WHITE);
	cpuid_t cpu_data = get_cpuid();
	kprintf(cpu_data.make, COLOR_WHITE);
	kprintf("\n", COLOR_WHITE);
	kprintf("Type: ", COLOR_WHITE);
	kprintf(itoa(cpu_data.family), COLOR_WHITE);
	kprintf("\n", COLOR_WHITE);
	kprintf("Family: ", COLOR_WHITE);
	kprintf(cpu_data.family, COLOR_WHITE);
	kprintf("\n", COLOR_WHITE);
	kprintf("Model: ", COLOR_WHITE);
	kprintf(cpu_data.model, COLOR_WHITE);
	kprintf("\n", COLOR_WHITE);
	kprintf("Enabling A20 Line...\n", COLOR_WHITE);
	enable_a20();
	kprintf("Initilizing VGA Driver....\n",COLOR_WHITE);
	kprintf("Installing Global Descriptor Table....\n",COLOR_WHITE);
	gdt_install();
	kprintf("Installing Interrupt Descriptor Table....\n",COLOR_WHITE);
	idt_install();
	kprintf("Enabling paging...\n", COLOR_WHITE);
	init_paging();
	kprintf("Setting up ISRs...\n",COLOR_WHITE);
	isrs_install();
	kprintf("Remapping the PIC and setting up IRQs...\n",COLOR_WHITE);
	install_irq();
	kprintf("Initializing the Kernel Address Translation Table...\n", COLOR_WHITE);
	kATT_Init();
	kprintf("Identifying ATA drives.....\n", COLOR_WHITE);
	ATA_Init();
	kprintf(DRIVE_DATA, COLOR_WHITE);
        kprintf("Installing Timer ISR....\n",COLOR_WHITE);
 	timer_install();
//	kprintf("Checking PCI device vendors....\n",COLOR_WHITE);
//	init_PCI();
	kprintf("Starting shell....\n",COLOR_WHITE);

	init_shell();

	for (;;);
}
