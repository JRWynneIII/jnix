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
	printk("Identifying CPU...", COLOR_WHITE);
	cpuid_t cpu_data = get_cpuid();
	printk(cpu_data.make, COLOR_WHITE);
	printk("\n", COLOR_WHITE);
	printk("Type: ", COLOR_WHITE);
	printk(itoa(cpu_data.family), COLOR_WHITE);
	printk("\n", COLOR_WHITE);
	printk("Family: ", COLOR_WHITE);
	printk(cpu_data.family, COLOR_WHITE);
	printk("\n", COLOR_WHITE);
	printk("Model: ", COLOR_WHITE);
	printk(cpu_data.model, COLOR_WHITE);
	printk("\n", COLOR_WHITE);
	printk("Initilizing VGA Driver....\n",COLOR_WHITE);
	printk("Installing Global Descriptor Table....\n",COLOR_WHITE);
	gdt_install();
	printk("Installing Interrupt Descriptor Table....\n",COLOR_WHITE);
	idt_install();
	printk("Setting up ISRs...\n",COLOR_WHITE);
	isrs_install();
	printk("Remapping the PIC and setting up IRQs...\n",COLOR_WHITE);
	install_irq();
	printk("Identifying ATA drives.....\n", COLOR_WHITE);
	ATA_Init();
	printk(DRIVE_DATA, COLOR_WHITE);
        printk("Installing Timer ISR....\n",COLOR_WHITE);
 	timer_install();
//	printk("Checking PCI device vendors....\n",COLOR_WHITE);
//	init_PCI();
	printk("Starting shell....\n",COLOR_WHITE);

	init_shell();

	for (;;);
}
