BITS	16
gdt_null_desc:
	dd	0
	dd	0

gdt_code_desc:
	dw	0xFFFF		; Limit
	dw	0x0000		; Base (low)
	db	0x00		; Base (medium)
	db	0b10011010	; Access byte
	db	0b11001111	; Flags + Upper Limit
	db	0x00		; Base (high)

gdt_data_desc:
	dw	0xFFFF		; Limit
	dw	0x0000		; Base (low)
	db	0x00		; Base (medium)
	db	0b10010010	; Access byte
	db	0b11001111	; Flags + Limit
	db	0x00		; Base (high)
gdt_end:

gdt_size:
	dw	gdt_end - gdt_null_desc - 1
	dd	gdt_null_desc


BITS	32
edit_gdt:
	mov	[gdt_code_desc + 6], byte 0b10101111
	mov	[gdt_data_desc + 6], byte 0b10101111
	ret
BITS	16

; Constants
code_seg	equ	gdt_code_desc - gdt_null_desc
data_seg	equ	gdt_data_desc - gdt_null_desc