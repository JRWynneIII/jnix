#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
#define PIC_READ_IRR 0x0a	//Raised IRQ
#define PIC_READ_ISR 0x0b
#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1
#define PIC_INIT 0x11

#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

extern void irq0();
extern void irq1();
extern void irq2();

//This will hold pointers to the apprpriate IRQ handlers for that interupt. (like keyboard)
void *irq_routines[16] = 
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

//installs custom IRQ handler for given irq. (stores pointer to funcion at given irq)
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq]=handler;
}

//clears handler for given IRQ
void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

void init_PIC()
{
	//PIC1 Command: 0x20	data: 0x21
	//PIC2 Command: 0xA0	data: 0xA1
	//Send a 0x20 to the Command Port for EOI
	//
	//0x11 = initialize command
	//	makes PIC wait for 3 more words
	//	fist: vector offset
	//	second: how it is wired to slave/master
	//	third: environment info
	


	//Save the PIC masks
	unsigned char mask1, mask2;
	mask1 = inportb(PIC1_DATA);
	mask2 = inportb(PIC2_DATA);

	//initialize the PICs
	outportb(PIC1_COMMAND, PIC_INIT);
	io_wait();
	outportb(PIC2_COMMAND, PIC_INIT);
	io_wait();
	//set vector table offset!!
	outportb(PIC1_DATA, 32);
	io_wait();
	outportb(PIC2_DATA, 40);
	io_wait();
	//tell master there is a slave at irq2
	outportb(PIC1_DATA, 4);
	io_wait();
	//tell slave its cascade identity??	
	outportb(PIC2_DATA, 2);
	io_wait();
	//put PICs into 8086 mode 
	outportb(PIC1_DATA, 0x01);
	io_wait();
	outportb(PIC2_DATA, 0x01);
	io_wait();
	//restore the saved masks
	outportb(PIC1_DATA, mask1);
	outportb(PIC2_DATA, mask2);

	
}

void irq_handler(struct regs *r)
{
	//blank function pointer
	void (*handler)(struct regs *r);
	//Do we have a custom IRQ handler for this interrupt??
	//if so, run it
	handler = irq_routines[r->int_no - 32];
	if (handler)
		handler(r);

	//send end of interrupt
	//must send 0x20 (EOI) to BOTH PICs if the IRQ came from the slave PIC (0xA0)
	if ((r->int_no-32)>=8)
		outportb(0xA0, 0x20);
	outportb(0x20, 0x20);
}

void install_irq()
{
	//reprogram the PICs
	init_PIC();
	//install the appropriate ISRs into the IDT
	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
  idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
  idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	//turn on interupts!
	__asm__ __volatile__("sti");
}
