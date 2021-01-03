#include "interrupt.h"

static UINT32 tick = 0;

void init_idt_desc(UINT16 select, UINT32 offset, UINT32 type, PIDT_ENTRY desc)
{
	desc->offset_lowerbits = (offset & 0xffff);
	desc->selector = select;
	desc->type_attr = type;
	desc->offset_higherbits = (offset & 0xffff0000) >> 16;
}

void idt_init(void)
{
	unsigned long keyboard_address;
	unsigned long pit_handler_address;

	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* IRQ0 - PIT Timer */
	pit_handler_address = (unsigned long)pit_handler;
		init_idt_desc(KERNEL_CODE_SEGMENT_OFFSET, pit_handler_address, INTERRUPT_GATE, &IDT[0x20]);

	/* IRQ1 - PS/2 keyboard */
	keyboard_address = (unsigned long)keyboard_handler;
		init_idt_desc(KERNEL_CODE_SEGMENT_OFFSET, keyboard_address, INTERRUPT_GATE, &IDT[0x21]);

	 /*     Ports
	 * * * * * * * * * *     
	 *	   PIC1	PIC2
	 * Command 0x20	0xA0
	 * Data	   0x21	0xA1
	 */

	/* ICW1 - begin initialization */
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (IDT_ENTRY) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void kb_enable(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard) */
	write_port(0x21, 0xFD);
}

void mask_disable(void)
{
    	/* 0xFF is 11111111 - disables all IRQ lines (keyboard) */
    	write_port(0x21, 0xFF);
}

void pit_init(UINT32 frequency)
{
	// TODO: I'm stupid and haven't implemented a mask toggle yet so whatever
	write_port(0x21, 0xFE);

	// The value we send to the PIT is the value to divide it's input clock
	// (1193180 Hz) by, to get our required frequency. Important to note is
	// that the divisor must be small enough to fit into 16-bits.
	UINT32 divisor = 1193180 / frequency;

	// Send the command byte.
	write_port(0x43, 0x36);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	BYTE lower = (BYTE)(divisor & 0xFF);
	BYTE upper = (BYTE)((divisor>>8) & 0xFF);

	// Send the frequency divisor.
	write_port(0x40, lower);
	write_port(0x40, upper);

	tick = 0;
}

void pit_handler_main(void)
{
	write_port(0x20, 0x20); // EOI
	++tick;
}

UINT32 KeGetTickCount(void)
{
	return tick;
}

void KeSleep(UINT32 ms)
{
	UINT32 cur_tick = KeGetTickCount();
	while(cur_tick <= ms)
	{
		cur_tick = KeGetTickCount();
	}
}
