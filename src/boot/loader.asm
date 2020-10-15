EXTERN		print_bios
;EXTERN		kernel_start
%include	"header.asm"

BITS	16

; ### Data ###
%include	"gdt.asm"
string2		db	"Entering proteted mode", 0

; ### Code ###
GLOBAL	loader_start
loader_start:
enter_protected_mode:
	; call	mem_detect
	PRINT_BIOS	string2
	; Enable A20
	in		al, 0x92
	or		al, 2
	out		0x92, al
	; Enable protected mode
	cli
	lgdt	[gdt_size]
	mov		eax, cr0
	or		eax, 1
	mov		cr0, eax
	jmp		code_seg:start_protected_mode

BITS		32
start_protected_mode:
	; Reassign segment registers
	mov		ax, data_seg
	mov		ds, ax
	mov		ss, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	; Initalize new stack
	mov		ebp, 0x90000
	mov		esp, ebp
	; Setup kernel
	call	detect_cpuid
	call	detect_long_mode
	call	setup_paging
	call	edit_gdt
	call	activate_sse
	; Go to kernel space
	;jmp		code_seg:kernel_start
	jmp		code_seg:KERNEL_SPACE

mem_detect:
	mov	ax, 0
	mov	es, ax
	mov	di, mem_map		; probably safe to store here
	mov	edx, 0x534D4150	; magic number
	mov	ebx, 0
	.repeat:
		mov	eax, 0xE820	; magic BIOS number
		mov	ecx, 24		; listing size
		int	0x15		; save listing
		cmp	ebx, 0
		je	.return
		add	di, 24
		inc	byte [mem_region_count]
		jmp	.repeat
	.return:
	ret
	
BITS		64
activate_sse:
	mov	rax, cr0
	and	ax, 0b11111101
	or	ax, 0b00000001
	mov	cr0, rax
	mov	rax, cr4
	or	ax, 0b1100000000
	mov	cr4, rax
	ret

; ### 32-bit Includes ###
BITS		32
%include	"lib/cpu32.asm"
%include	"lib/paging.asm"

; ## Variables ###
mem_map:
	db	0
GLOBAL	mem_region_count
mem_region_count:
	db	0

; ### Fill
TIMES		512-($-$$)	db	0