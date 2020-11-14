CC = gcc
CFLAGS = -fno-stack-protector -fno-pic -fno-builtin -nostdinc -I src -Wall -m32
ASMC = nasm
ASMCFLAGS = -f elf32
BUILDDIR = build

all: clean link 
	@echo "Done!"

link: basm.o kmain.o video.o
	ld -m elf_i386 -T link.ld -o kernel.bin $?

basm.o: src/kernel/boot.asm
	$(ASMC) $(ASMCFLAGS) $? -o $@

kmain.o: src/kmain.c 
	$(CC) $(CFLAGS) -c $?

video.o: src/kernel/video.c
	$(CC) $(CFLAGS) -c $?

clean:
	rm -f *.o *.bin
