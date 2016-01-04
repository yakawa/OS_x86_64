#include <kernel.h>
#include <irs.h>
#include <klib/io.h>

typedef struct _gate_descriptor {
	unsigned short offset_low;
	unsigned short selector;
	unsigned char reserve1;
	unsigned char type;
	unsigned short offset_mid;
	unsigned int offset_high;
	unsigned int reserve2;
} __attribute__ ((packed)) GATE_DESCRIPTOR;

typedef struct
{
	unsigned short    size;
	GATE_DESCRIPTOR*  base;
} __attribute__ ((packed)) IDTR;


GATE_DESCRIPTOR idt[256];
IDTR idtr;


void set_idt(GATE_DESCRIPTOR *desc, void *handler, unsigned short selector, unsigned char P, unsigned char DPL, unsigned char D)
{
	unsigned char flg = 0x0E;
	desc->reserve1 = 0x00;
	desc->reserve2 = 0x00;

	desc->offset_low  =  0x000000000000FFFF & (unsigned long)handler;
	desc->offset_mid  = (0x00000000FFFF0000 & (unsigned long)handler) >> 16;
	desc->offset_high = (0xFFFFFFFF00000000 & (unsigned long)handler) >> 32;
	desc->selector = selector;

	flg += (P & 0x01) << 7;
	flg += (DPL & 0x03) << 5;
	flg += (D & 0x01) << 3;
	desc->type = flg;
}

void setIDT64(void)
{
	int i;
	for(i = 0; i < 256; i++){
		set_idt(&idt[i], (void*)irs_ignore, 0x08, 1, 0, 0);
	}

	set_idt(&idt[0x00], (void *)irs_div_by_0, 0x08, 1, 0, 0); // 0除算 #DE  (Division by 0)
	set_idt(&idt[0x01], (void *)irs_ignore, 0x08, 1, 0, 0); // Debug #DB
	set_idt(&idt[0x02], (void *)irs_ignore, 0x08, 1, 0, 0); // Non maskable Interrupts
	set_idt(&idt[0x03], (void *)irs_ignore, 0x08, 1, 0, 0); // break point #BP int 03h
	set_idt(&idt[0x04], (void *)irs_ignore, 0x08, 1, 0, 0); // overflow #OF
	set_idt(&idt[0x05], (void *)irs_ignore, 0x08, 1, 0, 0); // Bounds Check #BR
	set_idt(&idt[0x06], (void *)irs_ignore, 0x08, 1, 0, 0); // 無効な命令 #UD (Undifined Operation Code instruction)
	set_idt(&idt[0x07], (void *)irs_ignore, 0x08, 1, 0, 0); // コプロセッサーがない #NM (No coprosessor)
	set_idt(&idt[0x08], (void *)irs_ignore, 0x08, 1, 0, 0); // Double Falt #DF
	set_idt(&idt[0x09], (void *)irs_ignore, 0x08, 1, 0, 0); // Coprocessor Segment Overrun #MF
	set_idt(&idt[0x0A], (void *)irs_ignore, 0x08, 1, 0, 0); // 無効なTSS #TS (Invalid TSS)
	set_idt(&idt[0x0B], (void *)irs_ignore, 0x08, 1, 0, 0); // セグメントエラー #NP (Segment Not Present)
	set_idt(&idt[0x0C], (void *)irs_ignore, 0x08, 1, 0, 0); // Stack Segment Fault #SS
	set_idt(&idt[0x0D], (void *)irs_ignore, 0x08, 1, 0, 0); // 一般保護例外 #GP
	set_idt(&idt[0x0E], (void *)irs_ignore, 0x08, 1, 0, 0); // ページフォールト #PF
	set_idt(&idt[0x10], (void *)irs_ignore, 0x08, 1, 0, 0); // 浮動小数点エラー #MF
	set_idt(&idt[0x11], (void *)irs_ignore, 0x08, 1, 0, 0); // アライメントエラー #AC
	set_idt(&idt[0x12], (void *)irs_ignore, 0x08, 1, 0, 0); // マシンチェック #MC
	set_idt(&idt[0x13], (void *)irs_ignore, 0x08, 1, 0, 0); // SIMDエラー #XF

 	set_idt(&idt[0x20], (void *)irs_timer, 0x08, 1, 0, 0); // タイマー


	idtr.size= 256 * sizeof(GATE_DESCRIPTOR);
	idtr.base= (GATE_DESCRIPTOR *)idt;

	__asm__("lidt idtr");
}

void initializePIC(void)
{
	io_cli();

	io_out8(PIC_MASTER_IMR, 0xff);
	io_out8(PIC_SLAVE_IMR, 0xff);

	io_out8(PIC_MASTER_COMMAND, 0x11);
	io_out8(PIC_MASTER_DATA, 0x20);
	io_out8(PIC_MASTER_DATA, 0x04);
	io_out8(PIC_MASTER_DATA, 0x01);

	io_out8(PIC_SLAVE_COMMAND, 0x11);
	io_out8(PIC_SLAVE_DATA, 0x28);
	io_out8(PIC_SLAVE_DATA, 0x02);
	io_out8(PIC_SLAVE_DATA, 0x01);

	io_out8(PIC_MASTER_IMR, 0xff);
	io_out8(PIC_SLAVE_IMR, 0xff);

	io_sti();
}

void kmain(unsigned long magic, unsigned long addr)
{
	if(magic != 0x36d76289){
		kprintf("Magic is ignore");
		return;
	}
	kputs("Hello MyOS.");
	kprintf("[DEBUG] magic %d\n", 4);

	setIDT64();
	kprintf("[INFO] set IDT\n");

	initializePIC();
	kprintf("[INFO] initialized PIC");

	startTimer();

	while(1){
		io_hlt();
	}

}
