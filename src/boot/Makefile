include ../Makefile.inc
CFLAGS += -I../include -I.

OBJS = loader.o

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *~

.PHONY: clean all
