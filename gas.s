# In just a few pages in this tutorial, we will add our Interrupt
# Service Routines (ISRs) right here!
.global _isr0
.global _isr1
.global _isr2
...:                # Fill in the rest here!
.global _isr30
.global _isr31

#  0: Divide By Zero Exception
_isr0: 
    cli
    pushb $0       # A normal ISR stub that pops a dummy error code to keep a
                   # uniform stack frame
    pushb $0
    jmp isr_common_stub

#  1: Debug Exception
_isr1: 
    cli
    pushb $0
    pushb $1
    jmp isr_common_stub

_isr1...:           # Fill in from 2 to 7 here!

#  8: Double Fault Exception (With Error Code!)
_isr8: 
    cli
    pushb $8           # Note that we DON'T push a value on the stack in this one!
                   # It pushes one already! Use this type of stub for exceptions
                   # that pop error codes!
    jmp isr_common_stub

_isr8...:           # You should fill in from _isr9 to _isr31 here. Remember to
                   # use the correct stubs to handle error codes and push dummies!

# We call a C function in here. We need to let the assembler know
# that '_fault_handler' exists in another file
.extern _fault_handler

# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
isr_common_stub: 
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    movw $0x10,%ax # Load the Kernel Data Segment descriptor!
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movl %esp,%eax # Push us the stack
    pushl %eax
    movl $_fault_handler, %eax
    call *%eax     # A special call, preserves the 'eip' register
    popl %eax
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    addl $8,%esp   # Cleans up the pushed error code and pushed ISR number
    iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

