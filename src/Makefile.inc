CC = gcc
LD = ld
ASM = nasm

CFLAGS = -m64
CFLAGS += -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding
CFLAGS += -Wall -Werror -c -masm=intel -mcmodel=kernel -O0

AS = nasm
ASFLAGS = -f elf64