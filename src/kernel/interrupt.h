#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "../common.h"
#include "io/video.h"
#include "io/keyboard.h"

#define IDT_SIZE 256

#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

typedef struct _IDT_ENTRY
{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
} IDT_ENTRY, * PIDT_ENTRY;

IDT_ENTRY IDT[IDT_SIZE];

extern void keyboard_handler(void);
extern BYTE read_port(UINT16 port);
extern void write_port(UINT16 port, BYTE data);
extern void load_idt(unsigned long *idt_ptr);

void idt_init(void);
void kb_enable(void);
void kb_disable(void);

#endif
