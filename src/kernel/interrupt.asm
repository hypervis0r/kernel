;; Port I/O code written in asm

extern keyboard_handler_main

global read_port
read_port: ; Read data from I/O port
	mov edx, [esp + 4]
	in al, dx
	ret

global write_port
write_port: ; Write data to I/O port
	mov   edx, [esp + 4]
	mov   al, [esp + 4 + 4]
	out   dx, al
	ret

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti 				;turn on interrupts
	ret

global keyboard_handler
keyboard_handler:
    call keyboard_handler_main
    iretd
