EXTERN	_idt
EXTERN	_isr1_handler

idt_descriptor:
	dw	4095
	dq	_idt

GLOBAL	_isr1
_isr1:
	PUSH_REG
	call	_isr1_handler
	POP_REG
	iretq

GLOBAL	_load_idt
_load_idt:
	lidt	[idt_descriptor]
	sti
	ret