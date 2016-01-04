include ../Makefile.inc
CFLAGS += -I../include -I.

OBJS = io.o io_asm.o

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *~

.PHONY: clean all
