CC = gcc
LD = ld
ASM = nasm

CFLAGS = -m64
CFLAGS += -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding
CFLAGS += -Wall -Werror -c -masm=intel -mcmodel=kernel
CFLAGS += -DDEBUG

AS = nasm
ASFLAGS = -f elf64