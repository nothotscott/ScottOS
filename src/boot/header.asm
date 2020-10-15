%define	PAGE_TABLE_ENTRY	0x1000
%define	BOOT_SPACE			0x7c00
%define	LOADER_SPACE		BOOT_SPACE + 512
%define	KERNEL_SPACE		LOADER_SPACE + 512

%define	OS_NAME				"ScottOS"

%macro PRINT_BIOS 1
	mov		bx, %1
	call	print_bios
%endmacro

; Disk read macro
; Example: DISK_READ KERNEL_SPACE, 4, 0, 0, 2
%macro	DISK_READ 5
	mov		bx, %1
	mov		al, %2
	mov 	ch, %3
	mov		dh, %4
	mov		cl, %5
	call	disk_read
%endmacro