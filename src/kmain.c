#include "common.h"
#include "kernel/video.h"
#include "kernel/interrupt.h"

void kmain(void)
{
    InitSTDOUT();
    
    kstdout->attrib = 0x4F;

    KeClearScreen(kstdout->attrib);
    KePrintK("TEST Enter keyboard input:\n");
    
    idt_init();
	kb_init();

    while(1);

    return;
}
