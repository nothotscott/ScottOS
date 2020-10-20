/* OUTPUT_FORMAT(binary) */
OUTPUT_FORMAT(elf64-x86-64)

INPUT
(
	kernel1.o
	kernel2.o
	library.o
	binaries.o
)

OUTPUT
(
	../bin/kernel.o
)

SECTIONS
{
	. = 0x8000;
	.text :ALIGN(4K)				/* Code */
	{
		*(.multiboot)
		*(.text)
	}
	.idt BLOCK(4K) : ALIGN(4K)		/* IDT */
	{
		_idt = ABSOLUTE(.);
		. = . + 4K;
	}
	.data BLOCK(4K) : ALIGN(4K)		/* Data */
	{
		*(.data)
	}
	.rodata BLOCK(4K) : ALIGN(4K)	/* Read-only data */
	{
		*(.rodata)
	}
	.bss BLOCK(4K) : ALIGN(4K)		/* Read-write data (uninitialized) and stack */
	{
		*(COMMON)
		*(.bss)
	}
}