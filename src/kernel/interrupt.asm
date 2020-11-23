;; Port I/O code written in asm

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

extern keyboard_handler_main
global keyboard_handler
keyboard_handler:
    pushad
    call keyboard_handler_main
    popad
    iretd

extern pit_handler_main
global pit_handler
pit_handler:
    pushad
    call pit_handler_main
    popad
    iretd
