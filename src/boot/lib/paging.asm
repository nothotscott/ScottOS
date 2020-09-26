BITS	32
; Identity paging (1:1 virtual to physical memory)
setup_paging:
	; Page table
	mov		edi, PAGE_TABLE_ENTRY
	mov		cr3, edi
	mov		dword [edi], 0x2003
	; 1 Page directory table
	add		edi, 0x1000
	mov		dword [edi], 0x3003
	; 2 Page directory pointer table
	add		edi, 0x1000
	mov		dword [edi], 0x4003
	; 3 Page map L4 table 
	add		edi, 0x1000
	mov		ebx, 0x00000003
	mov		ecx, 512
	.set_entry:
		mov		dword [edi], ebx
		add		ebx, 0x1000
		add		edi, 8
		loop	.set_entry
	; Physical address extention paging
	mov		eax, cr4
	or		eax, 1 << 5	; enable
	mov		cr4, eax
	; EFER model-specific register
	mov		ecx, 0xC0000080
	rdmsr
	or		eax, 1 << 8	; Enable long mode
	wrmsr
	; Enable paging
	mov		eax, cr0
	or		eax, 1 << 31
	mov		cr0, eax
	; Leave routine
	ret