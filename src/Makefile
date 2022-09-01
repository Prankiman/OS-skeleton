C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJ = ${C_SOURCES:.c=.o}

KERN=kernel.bin
BOOT=boot_kernel.bin

all: kernel.bin boot_kernel.bin

kernel.bin: enter_kernel.o ${OBJ} isrs.o irqs.o #cpu_reset.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary #-g option if you want to debug with gdb

%.o: %.c ${HEADERS}
	gcc -march=i386 -elf_i386 -m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wno-pointer-arith -Wno-unused-parameter -nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector -fno-builtin-function -fno-builtin -c $< -o $@

%.o: %.asm
	nasm $< -f elf32 -o $@

%.bin: %.asm
	nasm $< -o $@

clean:
	rm *.o *.bin boot.iso

iso: all
	dd if=/dev/zero of=boot.iso bs=512 count=2880
	dd if=./$(BOOT) of=boot.iso conv=notrunc bs=512 seek=0 count=1
	dd if=./$(KERN) of=boot.iso conv=notrunc bs=512 seek=1 count=2048

