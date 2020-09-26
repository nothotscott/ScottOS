BITS	32
; Detect if changing the ID bit changes
detect_cpuid:
	pushfd
	pop		eax				; EFLAGS=eax
	mov		ecx, eax
	; Flip and set back EFLAGS
	xor		eax, 1 << 21	; flip bit 21(ID)
	push	eax
	popfd
	; Re-set EFLAGS=eax
	pushfd
	pop		eax
	; Restore old EFLAGS
	push	ecx
	popfd
	; Compare flags
	xor		eax, ecx
	jz		.no_cpuid
	ret
	.no_cpuid:
		hlt

detect_long_mode:
	mov		eax, 0x80000001
	cpuid
	test	edx, 1 << 29 ; cmp?
	jz		.no_long_mode
	ret
	.no_long_mode:
		hlt