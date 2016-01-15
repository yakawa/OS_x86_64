include ../Makefile.inc
CFLAGS += -I../include -I.

OBJS = kernel.o kernel_asm.o irs.o irs_func.o timer.o bootinfo.o

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *~

.PHONY: clean all
