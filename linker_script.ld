ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY {
	FLASH (rx): ORIGIN = 0x08000000, LENGTH = 1M
	RAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS {
	.isr_vector :
	{
		KEEP(*(.isr_vector))
	} >FLASH

	.text :
	{
		. = ALIGN(4);

		*(.text)
		*(.rodata)

		. = ALIGN(4);
		_etext = .;
	} >FLASH

	_sidata = LOADADDR(.data);

	.data :
	{
		. = ALIGN(4);
		_sdata = .;

		*(.data)

		. = ALIGN(4);
		_edata = .;
	} >RAM AT> FLASH

	.bss :
	{
		. = ALIGN(4);
		_sbss = .;

		*(.bss)

		. = ALIGN(4);
		_ebss = .;
	} >RAM
}
