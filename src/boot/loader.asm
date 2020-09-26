loader_start:				; always on first line
BITS	16

jmp	short enter_protected_mode
nop

; ### Data ###
%include	"gdt.asm"

; ### Code ###
enter_protected_mode:
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
	; Setup & Load kernel
	call	detect_cpuid
	call	detect_long_mode
	call	setup_paging
	call	edit_gdt
	jmp		code_seg:KERNEL_SPACE
	

; ### 32-bit Includes ###
BITS		32
%include	"lib/cpu32.asm"
%include	"lib/paging.asm"

; ### Fill
TIMES		512-($-loader_start)	db	0