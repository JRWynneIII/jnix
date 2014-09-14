;32: IRQ0
_irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_common_stub

extern _irq_handler
