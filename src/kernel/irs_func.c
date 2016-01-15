#include <kernel.h>
#include <klib/io.h>

void irs_ignore_func(void)
{
	kmsg(KM_EMERG, "Exception: Unknown Exception");
	return;
}

void DE_func(void)
{
	kmsg(KM_EMERG, "Exception: Division by 0 #DE");
	return;
}

void DB_func(void)
{
	kmsg(KM_INFO, "Exception: Single Step (Debug) #DB");
	return;
}

void NMI_func(void)
{
	kmsg(KM_EMERG, "Exception: Non-Maskable Interrupt");
	return;
}

void BP_func(void)
{
	kmsg(KM_INFO, "Exception: Break Point (Debug) #BP");
	return;
}

void OF_func(void)
{
	kmsg(KM_EMERG, "Exception: Overflow #OF");
	return;
}

void BR_func(void)
{
	kmsg(KM_EMERG, "Exception: Bounds Check #BR");
	return;
}

void UD_func(void)
{
	kmsg(KM_EMERG, "Exception: Undifined Operation Code Instruction #UD");
	return;
}

void NM_func(void)
{
	kmsg(KM_EMERG, "Exception: No Coprocessor #BP");
	return;
}

void DF_func(void)
{
	kmsg(KM_EMERG, "Exception: Double Fault #DF");
	return;
}

void coprocessor_func(void)
{
	kmsg(KM_EMERG, "Exception: Coprocessor Segment Overrun #MF");
	return;
}

void TS_func(void)
{
	kmsg(KM_EMERG, "Exception: Invalid TSS #BP");
	return;
}

void NP_func(void)
{
	kmsg(KM_EMERG, "Exception: Segment Not Present #NP");
	return;
}

void SS_func(void)
{
	kmsg(KM_EMERG, "Exception: Stack Segment Fault #BP");
	return;
}

void GP_func(void)
{
	kmsg(KM_EMERG, "Exception: General Protection Fault #GP");
	return;
}

void PF_func(unsigned long address, unsigned long code, unsigned long rip)
{
	/*
		kprintf("Exception:");
	kprintf("Page Fault #PF\n");
	kprintf("Address:");
	kprinthexl(address);
	kprintf("\n");
	kprintf("Code:");
	kprinthexl(code);
	kprintf("RIP:");
	kprinthexl(rip);
	*/
	kmsg(KM_EMERG, "Exception: Page Fault #PF");
	return;
}

void MF_func(void)
{
	kmsg(KM_EMERG, "Exception: Corpocessor Error #MF");
	return;
}

void AC_func(void)
{
	kmsg(KM_EMERG, "Exception: Alignment Check #AF");
	return;
}

void MC_func(void)
{
	kmsg(KM_EMERG, "Exception: Machine Check #MC");
	return;
}

void XF_func(void)
{
	kmsg(KM_EMERG, "Exception: SIMD FPU Exception #BP");
	return;
}
