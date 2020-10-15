BITS	16
disk_string1	db	"Disk read error", 0	


; bx = Memory location
; al = Number of sectors
; ch = Cylinder number
; dh = Head number
; cl = Sector number
GLOBAL	disk_read
disk_read:
	mov		ah, 0x02			; read disk byte
	int		0x13				; BIOS interrupt
	jc		disk_read_error
	ret


disk_read_error:
	PRINT_BIOS	disk_string1