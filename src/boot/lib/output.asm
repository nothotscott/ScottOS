BITS	16
; bx = String address
GLOBAL	print_bios
print_bios:
	mov	ah, 0x0e				; magic high byte
	.feed:
		cmp	[bx], byte 0x00
		je	.return
		mov	al, [bx]
		int	0x10
		inc	bx
		jmp	.feed
	.return:
		ret