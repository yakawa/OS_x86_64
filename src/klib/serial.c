#include <kernel.h>
#include <klib/io.h>
#include <klib/serial.h>

void initializeSerial(void)
{
	io_out8(0x03F8 + 1, 0x00);
	io_out8(0x03F8 + 3, 0x80);
	io_out8(0x03F8 + 0, 0x03);
	io_out8(0x03F8 + 1, 0x00);
	io_out8(0x03F8 + 3, 0x03);
	io_out8(0x03F8 + 2, 0xC7);
	io_out8(0x03F8 + 4, 0x0B);
}

static int isTransmitEmpty() {
	return io_in8(0x03F8 + 5) & 0x20;
}

void writeSerial(unsigned char ch) {
	while (isTransmitEmpty() == 0);

	io_out8(0x03F8, ch);
}
