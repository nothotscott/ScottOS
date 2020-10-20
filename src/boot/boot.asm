; Copyright 2020 Scott Maday
; The bootloader is divided into 3 sections
; [1] boot.asm		Boots into 16-bit BIOS
; [2] loader.asm	Enters 64-bit long mode
; [3] The rest of the kernel
%include	"header.asm"

BITS	16
ORG		BOOT_SPACE

jmp			short main
nop


; ### Data ###
boot_disk	db	0

string1		db	OS_NAME, " BIOS loaded", 0


; ### Main ###
main:
	; Inital setup
	mov			bp, BOOT_SPACE		; Begin stack
	mov			sp, bp
	mov			[boot_disk], dl		; disk boot number from BIOS

	; Feedback
	PRINT_BIOS	string1

	; Fetch loader & kernel
	DISK_READ	LOADER_SPACE, 1, 0, 0, 2
	DISK_READ	KERNEL_SPACE, 60, 0, 0, 3
	jmp			LOADER_SPACE

; ### Includes ###
%include	"lib/output.asm"
%include	"lib/disk16.asm"

; ### Fill + magic
TIMES		510-($-$$)	db	0
dw			0xaa55

; ### Loader ###
;%include	"loader.asm"