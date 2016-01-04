#ifndef __KERNEL_H__
#define __KERNEL_H__

#define PIC_MASTER_COMMAND  0x20
#define PIC_MASTER_STATUS   0x20
#define PIC_MASTER_DATA     0x21
#define PIC_MASTER_IMR      0x21

#define PIC_SLAVE_COMMAND   0xA0
#define PIC_SLAVE_STATUS    0xA0
#define PIC_SLAVE_DATA      0xA1
#define PIC_SLAVE_IMR       0xA1

void kmain(unsigned long magic, unsigned long addr);
void startTimer(void);

#endif
