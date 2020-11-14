CC = gcc
CFLAGS = -fno-stack-protector -fno-pic -fno-builtin -nostdinc -I src -Wall -m32
ASMC = nasm
ASMCFLAGS = -f elf32

all: clean link 
	@echo "Done!"

link: basm.o kmain.o video.o keyboard_map.o interrupt.o interruptasm.o
	ld -m elf_i386 -T link.ld -o kernel.bin $?

basm.o: src/kernel/boot.asm
	$(ASMC) $(ASMCFLAGS) $? -o $@

interruptasm.o: src/kernel/interrupt.asm
	$(ASMC) $(ASMCFLAGS) $? -o $@

interrupt.o: src/kernel/interrupt.c 
	$(CC) $(CFLAGS) -c $<

keyboard_map.o: src/kernel/keyboard_map.c
	$(CC) $(CFLAGS) -c $<

kmain.o: src/kmain.c 
	$(CC) $(CFLAGS) -c $<

video.o: src/kernel/video.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.bin
