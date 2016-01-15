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

#define KM_NONE      255
#define KM_DEBUG     1
#define KM_INFO      2
#define KM_NOTICE    3
#define KM_WARNING   4
#define KM_ERROR     5
#define KM_CRITICAL  6
#define KM_ALERT     7
#define KM_EMERG     8

#define KM_TRUE  1
#define KM_FALSE 0

typedef struct _system_info {
	unsigned char log_level;
	unsigned char swap_sys;
	unsigned long memory_size;
} SYSTEM_INFO;

SYSTEM_INFO sys_info;

void kmain(unsigned long magic, void *addr);
void startTimer(void);

#endif
