CC = gcc
CFLAGS = -fno-stack-protector -fno-pic -fno-builtin -nostdinc -I src -Wall -m32
ASMC = nasm
ASMCFLAGS = -f elf32

all: clean link 
	@echo "Done!"

link: basm.o kmain.o video.o keyboard.o interrupt.o interruptasm.o input.o string.o
	ld -m elf_i386 -T link.ld -o kernel.bin $?

basm.o: src/kernel/boot.asm
	$(ASMC) $(ASMCFLAGS) $? -o $@

interruptasm.o: src/kernel/interrupt.asm
	$(ASMC) $(ASMCFLAGS) $? -o $@

interrupt.o: src/kernel/interrupt.c 
	$(CC) $(CFLAGS) -c $<

keyboard.o: src/kernel/io/keyboard.c
	$(CC) $(CFLAGS) -c $<

kmain.o: src/kmain.c 
	$(CC) $(CFLAGS) -c $<

video.o: src/kernel/io/video.c
	$(CC) $(CFLAGS) -c $<

input.o: src/kernel/io/input.c
	$(CC) $(CFLAGS) -c $<

string.o: src/libc/string.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.bin
