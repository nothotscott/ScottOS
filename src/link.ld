OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT
(
	kernel1.o
	kernel2.o
	library.o
)

OUTPUT
(
	../bin/kernel.bin
)

SECTIONS
{
	. = 0x8000;
	.text : ALIGN(4K)		/* Code */
	{
		*(.text)
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