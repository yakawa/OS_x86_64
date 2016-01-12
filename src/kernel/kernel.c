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

	set_idt(&idt[0x00], (void *)irs_DE, 0x08, 1, 0, 0); // 0除算 #DE  (Division by 0)
	set_idt(&idt[0x01], (void *)irs_DB, 0x08, 1, 0, 0); // Debug #DB
	set_idt(&idt[0x02], (void *)irs_NMI, 0x08, 1, 0, 0); // Non maskable Interrupts
	set_idt(&idt[0x03], (void *)irs_BP, 0x08, 1, 0, 0); // break point #BP int 03h
	set_idt(&idt[0x04], (void *)irs_OF, 0x08, 1, 0, 0); // overflow #OF
	set_idt(&idt[0x05], (void *)irs_BR, 0x08, 1, 0, 0); // Bounds Check #BR
	set_idt(&idt[0x06], (void *)irs_UD, 0x08, 1, 0, 0); // 無効な命令 #UD (Undifined Operation Code instruction)
	set_idt(&idt[0x07], (void *)irs_NM, 0x08, 1, 0, 0); // コプロセッサーがない #NM (No coprosessor)
	set_idt(&idt[0x08], (void *)irs_DF, 0x08, 1, 0, 0); // Double Falt #DF
	set_idt(&idt[0x09], (void *)irs_coprocessor, 0x08, 1, 0, 0); // Coprocessor Segment Overrun #MF
	set_idt(&idt[0x0A], (void *)irs_TS, 0x08, 1, 0, 0); // 無効なTSS #TS (Invalid TSS)
	set_idt(&idt[0x0B], (void *)irs_NP, 0x08, 1, 0, 0); // セグメントエラー #NP (Segment Not Present)
	set_idt(&idt[0x0C], (void *)irs_SS, 0x08, 1, 0, 0); // Stack Segment Fault #SS
	set_idt(&idt[0x0D], (void *)irs_GP, 0x08, 1, 0, 0); // 一般保護例外 #GP
	set_idt(&idt[0x0E], (void *)irs_PF, 0x08, 1, 0, 0); // ページフォールト #PF
	set_idt(&idt[0x10], (void *)irs_MF, 0x08, 1, 0, 0); // 浮動小数点エラー #MF
	set_idt(&idt[0x11], (void *)irs_AC, 0x08, 1, 0, 0); // アライメントエラー #AC
	set_idt(&idt[0x12], (void *)irs_MC, 0x08, 1, 0, 0); // マシンチェック #MC
	set_idt(&idt[0x13], (void *)irs_XF, 0x08, 1, 0, 0); // SIMDエラー #XF

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
struct multiboot_tag
{
	unsigned int type;
	unsigned int size;
};
struct multiboot_mmap_entry
{
	unsigned long addr;
	unsigned long len;
	unsigned int type;
	unsigned int zero;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;
struct multiboot_tag_mmap
{
	unsigned int type;
	unsigned int size;
	unsigned int entry_size;
	unsigned int entry_version;
	struct multiboot_mmap_entry entries[0];
};
void printBootInfo(void * addr)
{
	unsigned int size;
	kprinthexl((unsigned long)addr);kprintf("\n");
	size = *(unsigned int *)addr;
	kprintf("Size:");
	kprinthexs(size);
	kprintf("\n");

	//	for(tag = *(unsigned int*)(addr); addr <= end_addr;){// addr += *(unsigned int*)(addr + 4)){
	struct multiboot_tag *tag;
  for (tag = (struct multiboot_tag *) (addr + 8);
			 tag->type != 0;
			 tag = (struct multiboot_tag *) ((unsigned char *) tag + ((tag->size + 7) & ~7))){
		kprintf("Tag:");kprinthexs(tag->type);kprintf("Size:");kprinthexs(tag->size);kprintf("\n");
		if(tag->type == 6){
			multiboot_memory_map_t *mmap;
			for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
					 (unsigned char *) mmap < (unsigned char *) tag + tag->size;
					 mmap = (multiboot_memory_map_t *)((unsigned long) mmap	+ ((struct multiboot_tag_mmap *) tag)->entry_size)) {
				/*kprintf("base_addr = "); kprinthexl(mmap->addr);
				kprintf(" length = "); kprinthexl(mmap->len);
				kprintf(" type = "); kprinthexc(mmap->type);
				kprintf("\n");*/
				kprinthexl(mmap->addr);kputchar('-'); kprinthexl(mmap->addr + mmap->len); kprintf("("); kprinthexl(mmap->len); kprintf(")");
				switch(mmap->type){
				case 1:
					kprintf(" AVL");
					break;
				case 3:
					kprintf(" ACPI");
					break;
				case 4:
					kprintf(" RSV");
					break;
				default:
					kprintf(" Unknown(");	kprinthexc(mmap->type);	kprintf(")");
				}
				kprintf("\n");
			}
		}
	}
}

void kmain(unsigned long magic, void * addr)
{
	if(magic != 0x36d76289){
		kprintf("Magic is ignore");
		return;
	}

	printBootInfo(addr);

	setIDT64();
	kprintf("[INFO] set IDT\n");

	initializePIC();
	kprintf("[INFO] initialized PIC\n");

	startTimer();
	kprintf("[INFO] Start Timer\n");

	kputs("Hello MyOS.");

	while(1){
		io_hlt();
	}

}
