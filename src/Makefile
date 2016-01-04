include ./Makefile.inc

boot_dir = boot
kernel_dir = kernel
klib_dir = klib

OBJECTS = $(boot_dir)/loader.o \
					$(kernel_dir)/kernel.o \
					$(kernel_dir)/irs.o \
					$(kernel_dir)/irs_func.o \
					$(kernel_dir)/timer.o \
					$(klib_dir)/io.o \
					$(klib_dir)/io_asm.o

LDFLAGS = -T link.ld -Map os.map -z max-page-size=0x1000

all: os.iso

kernel.elf: build $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

build:
	cd $(boot_dir) && make
	cd $(kernel_dir) && make
	cd $(klib_dir) && make

os.iso: kernel.elf
	cp kernel.elf ../iso/boot/kernel.elf
	grub-mkrescue -o ../os.iso ../iso

run: os.iso
	bochs -f ../bochs.rc -q

clean:
	rm -rf *.o kernel.elf ../os.iso os.map
	cd $(boot_dir) && make clean
	cd $(kernel_dir) && make clean
	cd $(klib_dir) && make clean

.PHONY: clean all
