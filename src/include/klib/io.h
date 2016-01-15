#ifndef __KLIB_IO_H__
#define __KLIB_IO_H__

/* font attribution */
#define FB_BLACK         0x00
#define FB_BLUE          0x01
#define FB_GREEN         0x02
#define FB_CYAN          0x03
#define FB_RED           0x04
#define FB_MAGENTA       0x05
#define FB_BROWN         0x06
#define FB_LIGHT_GRAY    0x07
#define FB_DARK_GRAY     0x08
#define FB_LIGHT_BLUE    0x09
#define FB_LIGHT_GREEN   0x0A
#define FB_LIGHT_CYAN    0x0B
#define FB_LIGHT_RED     0x0C
#define FB_LIGHT_MAGENTA 0x0D
#define FB_LIGHT_BROWN   0x0E
#define FB_WHITE         0x0F

#define io_hlt() ({__asm__ __volatile__("hlt");})
#define io_cli() ({__asm__ __volatile__("cli");})
#define io_sti() ({__asm__ __volatile__("sti");})


int kputchar(int c);
void kmsg(const unsigned char msgLebel, const char *fmt);
void kmsg_lll(const unsigned char msgLebel, const char *fmt, unsigned long p1, unsigned long p2, unsigned long p3);
void kmsg_iii(const unsigned char msgLebel, const char *fmt, unsigned int p1, unsigned int p2, unsigned int p3);
void kmsg_lls(const unsigned char msgLebel, const char *fmt, unsigned long p1, unsigned long p2, char *p3);

void kprinthexc(unsigned char v);
void kprinthexs(unsigned short v);
void kprinthexi(unsigned int v);
void kprinthexl(unsigned long v);

void io_out8(unsigned short address, unsigned char val);
unsigned char io_in8(unsigned short address);

#endif
