/* OUTPUT_FORMAT(binary) */
/* OUTPUT_FORMAT(elf64-x86-64) */
OUTPUT_FORMAT(elf64-x86-64)

/* ENTRY(kernel_start) */
ENTRY(kernel_start)

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
	.text :ALIGN(4K)		/* Code */
	{
		*(.text)
	}
	.idt BLOCK(4K) : ALIGN(4K)
	{
		_idt = .;
		. = . + 4K;
	}
	.data : ALIGN(4K)		/* Data */
	{
		*(.data)
	}
	.rodata : ALIGN(4K)		/* Read-only data */
	{
		*(.rodata)
	}
	.bss : ALIGN(4K)		/* Read-write data (uninitialized) and stack */
	{
		*(COMMON)
		*(.bss)
	}
}