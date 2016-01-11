#include <kernel.h>
#include <klib/io.h>

void irs_ignore_func(void)
{
	kprintf("Exception:");
	kprintf("Unknown Exception");
	return;
}

void DE_func(void)
{
	kprintf("Exception:");
	kprintf("Division by 0 #DE");
	return;
}

void DB_func(void)
{
	kprintf("Exception:");
	kprintf("Single Step (Debug) #DB");
	return;

}

void NMI_func(void)
{
	kprintf("Exception:");
	kprintf("Non-Maskable Interrupt");
	return;

}

void BP_func(void)
{
	kprintf("Exception:");
	kprintf("Break Point (Debug) #BP");
	return;
}

void OF_func(void)
{
	kprintf("Exception:");
	kprintf("Overflow #OF");
	return;
}

void BR_func(void)
{
	kprintf("Exception:");
	kprintf("Bounds Check #BR");
	return;
}

void UD_func(void)
{
	kprintf("Exception:");
	kprintf("Undifined Operation Code Instruction #UD");
	return;
}

void NM_func(void)
{
	kprintf("Exception:");
	kprintf("No Coprocessor #BP");
	return;
}

void DF_func(void)
{
	kprintf("Exception:");
	kprintf("Double Fault #DF");
	return;
}

void coprocessor_func(void)
{
	kprintf("Exception:");
	kprintf("Coprocessor Segment Overrun #MF");
	return;
}

void TS_func(void)
{
	kprintf("Exception:");
	kprintf("Invalid TSS #BP");
	return;
}

void NP_func(void)
{
	kprintf("Exception:");
	kprintf("Segment Not Present #NP");
	return;
}

void SS_func(void)
{
	kprintf("Exception:");
	kprintf("Stack Segment Fault #BP");
	return;
}

void GP_func(void)
{
	kprintf("Exception:");
	kprintf("General Protection Fault #GP");
	return;
}

void PF_func(void)
{
	kprintf("Exception:");
	kprintf("Page Fault #PF");
	return;
}

void MF_func(void)
{
	kprintf("Exception:");
	kprintf("Corpocessor Error #MF");
	return;
}

void AC_func(void)
{
	kprintf("Exception:");
	kprintf("Alignment Check #AF");
	return;
}

void MC_func(void)
{
	kprintf("Exception:");
	kprintf("Machine Check #MC");
	return;
}

void XF_func(void)
{
	kprintf("Exception:");
	kprintf("SIMD FPU Exception #BP");
	return;
}
