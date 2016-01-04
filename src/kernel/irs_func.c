#include <kernel.h>
#include <klib/io.h>

void irs_ignore_func(void)
{
	kprintf("Exception:");
	kprintf("Unknown Exception");
	return;
}

void div_by_0_func(void)
{
	kprintf("Exception:");
	kprintf("Division by 0");
	return;
}
