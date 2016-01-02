KVMA_BASE = 0xFFFFFFFF80000000;
KLNA_BASE = 0x100000;

ENTRY(start)
SECTIONS
{
				. = KLNA_BASE;
				_kernel_start = .;

				.boot : {
							*(.boot_text)
							*(.boot_data)
				}

				. += KVMA_BASE;
				.text : AT(ADDR(.text) - KVMA_BASE) {
							*(.text)
							_rodata_start = .;
							*(.rodata)
							_rodata_end = .;
				}

				.data : AT(ADDR(.data) - KVMA_BASE) {
							_data_start = .;
							*(.data)
							_data_end = .;
				}

				.bss :  AT(ADDR(.bss) - KVMA_BASE) {
						 _bss_start = .;
						 *(.bss)
						 _bss_end = .;
				}

				.heap_early : AT(ADDR(.heap_early) - KVMA_BASE)	{
							_heap_early_start  = .;
							. += 0x8000;
							_heap_early_end = .;

				}

				. = ALIGN(0x1000);
				_kernel_end = . - KVMA_BASE;
}
