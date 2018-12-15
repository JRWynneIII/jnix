#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "vga.h"

void init_paging();

extern void enable_a20();

void printPrettyTime();

void runShell(char* command);

void** kmalloc(size_t size);

void kATT_Init();

void outportb (unsigned short _port, unsigned char _data);

unsigned char inl(unsigned short _port);

void outl(unsigned short _port, unsigned char _data);

void wait(int ticks);

static inline void io_wait(void)
{
    /* TODO: This is probably fragile. */
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}

void *memcpy(void *dest, const void *src, size_t count);

//unsigned char *memset(unsigned char *dest, unsigned char val, int count);
void *memset(void *dest, char val, size_t count);

//unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);

size_t strlen(const char* str);

unsigned char inportb (unsigned short _port);

void gdt_install();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void idt_install();

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void isrs_install();
void timer_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void install_irq();
void init_shell();
unsigned char inb(unsigned short _port);
void outb(unsigned short _port, unsigned char _data);


#endif
