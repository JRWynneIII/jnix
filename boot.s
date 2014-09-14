.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

#multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	call kernel_main
	cli
	hlt
.Lhang:
	jmp .Lhang
#set the size of _start to current location minus position of _start. 
.size _start, . - _start


# This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
# This is declared in C as 'extern void gdt_flush();'
.global gdt_flush    # Allows the C code to link to this
.extern gp           # Says that '_gp' is in another file
gdt_flush: 
    lgdt gp          # Load the GDT with our '_gp' which is a special pointer
    movw $0x10,%ax    # 0x10 is the offset in the GDT to our data segment
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ss
    jmp $0x08,$flush2   # 0x08 is the offset to our code segment: Far jump!
flush2: 
    ret
#Loads the IDT defined in _idtp into the processor
# This is declared in C as 'extern void idt_load();'

.global idt_load
.extern idtp
idt_load:
	lidt idtp
	ret

# In just a few pages in this tutorial, we will add our Interrupt
# Service Routines (ISRs) right here!
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

.global irq0
.global irq1
.global irq2

#  0: Divide By Zero Exception
isr0: 
    cli
    pushl $0       # A normal ISR stub that pops a dummy error code to keep a
                   # uniform stack frame
    pushl $0
    jmp isr_common_stub

#  1: Debug Exception
isr1: 
    cli
    pushl $0
    pushl $1
    jmp isr_common_stub

# 2: Non Maskable Interrupt Exception
isr2:
    cli
    pushl $0
    pushl $2
    jmp isr_common_stub

# 3: Breakpoint Exception
isr3:
	cli
	pushl $0
	pushl $3
	jmp isr_common_stub

# 4: Into detected overflow exception
isr4:
	cli
	pushl $0
	pushl $4
	jmp isr_common_stub

# 5: Out of Bounds exception
isr5:
	cli
	pushl $0
	pushl $5
	jmp isr_common_stub

# 6: Invalid Opcode exception
isr6:
	cli
	pushl $0
	pushl $6
	jmp isr_common_stub

# 7: No coprocessor exception
isr7:
	cli
	pushl $0
	pushl $6
	jmp isr_common_stub
	 
#  8: Double Fault Exception (With Error Code!)
isr8: 
    cli
    pushl $8           # Note that we DON'T push a value on the stack in this one!
                       # It pushes one already! Use this type of stub for exceptions
                       # that pop error codes!
    jmp isr_common_stub

                       # You should fill in from _isr9 to _isr31 here. Remember to
                       # use the correct stubs to handle error codes and push dummies!

# 9: Coprocessor Segment overrun exceptin
isr9:
	cli
	pushl $0
	pushl $9
	jmp isr_common_stub

# 10: Bad TSS exception
isr10:
	cli
	pushl $10
	jmp isr_common_stub

# 11: Segment not present exception
isr11:
	cli
	pushl $11
	jmp isr_common_stub

# 12: Stack Fault exception
isr12:
	cli
	pushl $12
	jmp isr_common_stub

# 13: General Protection Fault exception
isr13:
	cli
	pushl $13
	jmp isr_common_stub

# 14: Page Fault exception
isr14:
	cli
	pushl $14
	jmp isr_common_stub

# 15: REserved
isr15:
	cli
	pushl $0
	pushl $15
	jmp isr_common_stub

# 16: Floating Point Exception
isr16:
	cli
	pushl $0
	pushl $16
	jmp isr_common_stub

# 17: Alignment Check Exception
isr17:
	cli
	pushl $0
	pushl $17
	jmp isr_common_stub

# 18: Machine Check Exception
isr18:
	cli
	pushl $0
	pushl $18
	jmp isr_common_stub

# 19: Reserved
isr19:
	cli
	pushl $0
	pushl $19
	jmp isr_common_stub


# 19: Reserved
isr20:
	cli
	pushl $0
	pushl $20
	jmp isr_common_stub

# 19: Reserved
isr21:
	cli
	pushl $0
	pushl $21
	jmp isr_common_stub

# 19: Reserved
isr22:
	cli
	pushl $0
	pushl $22
	jmp isr_common_stub

isr23:
	cli
	pushl $0
	pushl $23
	jmp isr_common_stub

isr24:
	cli
	pushl $0
	pushl $24
	jmp isr_common_stub

isr25:
	cli
	pushl $0
	pushl $25
	jmp isr_common_stub

isr26:
	cli
	pushl $0
	pushl $26
	jmp isr_common_stub

isr27:
	cli
	pushl $0
	pushl $27
	jmp isr_common_stub

isr28:
	cli
	pushl $0
	pushl $28
	jmp isr_common_stub

isr29:
	cli
	pushl $0
	pushl $29
	jmp isr_common_stub

isr30:
	cli
	pushl $0
	pushl $30
	jmp isr_common_stub

isr31:
	cli
	pushl $0
	pushl $31
	jmp isr_common_stub

# We call a C function in here. We need to let the assembler know
# that '_fault_handler' exists in another file
.extern fault_handler

# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
isr_common_stub: 
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    movw $0x10,%ax # Load the Kernel Data Segment descriptor!
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movl %esp,%eax # Push us the stack
    pushl %eax
    movl $fault_handler, %eax
    call *%eax     # A special call, preserves the 'eip' register
    popl %eax
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    addl $8,%esp   # Cleans up the pushed error code and pushed ISR number
    iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!


irq0:
	cli
	pushl $0
	pushl $32
	jmp irq_common_stub

irq1:
	cli
	pushl $0
	pushl $33
	jmp irq_common_stub

irq2:
	cli
	pushl $0
	pushl $34
	jmp irq_common_stub

.extern irq_handler

irq_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	mov $0x10,%ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp,%eax
	push %eax
	mov $irq_handler,%eax
	call *%eax
	pop %eax
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	addl $8,%esp
	iret

#create the stack
.section .bootstrap_stack
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

