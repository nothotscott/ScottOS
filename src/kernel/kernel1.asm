BITS	64
EXTERN	_start

clear_screen:
	mov	edi, 0xb8000
	mov	rax, 0x1f201f201f201f20
	mov	ecx, 500
	rep	stosq

call	_start
hlt

TIMES		512-($-$$)	db	0