CC = gcc
LD = ld
ASM = nasm

CFLAGS = -m64
CFLAGS += -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
CFLAGS += -Wall -Werror -c -masm=intel

AS = nasm
ASFLAGS = -f elf64