#include <kernel.h>
#include <klib/io.h>

static unsigned long long tmr0;

void startTimer(void)
{
	io_out8(PIC_MASTER_IMR, 0xF8);
}


void timer_func(void)
{
	tmr0 += 1;
	io_out8(0x20, 0x20);
}
