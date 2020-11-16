#include "interrupt.h"

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
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler;
	init_idt_desc(KERNEL_CODE_SEGMENT_OFFSET, keyboard_address, INTERRUPT_GATE, &IDT[0x21]);
    
    /*     Ports
     * * * * * * * * * *     
	 *	       PIC1	PIC2
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
