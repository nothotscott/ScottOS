BITS		64
EXTERN		main
%include	"macros.asm"
; %include	"../boot/header.asm"

jmp			kernel_start
%include	"io/idt.asm"

; ### Main Code ###
GLOBAL	kernel_start
kernel_start:
	call	main
	jmp		$
	hlt

; ### Fill
TIMES		512-($-$$)	db	0