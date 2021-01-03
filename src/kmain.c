#include "common.h"
#include "kernel/io/video.h"
#include "kernel/io/input.h"
#include "kernel/interrupt.h"

void kmain(void)
{
    kstdout_init();
    kstdin_init();
    idt_init();
    pit_init(1000); // 1000 hz == 1ms

    kstdout->attrib = 0x4F;

    KePrintK("Waiting for 2 seconds...\n");
    KeSleep(2000); /* Sleep for 2 seconds (to demonstrate PIT timer) */

    KeClearScreen(kstdout->attrib);
    KePrintK("TEST Enter keyboard input:\n");

    char str[50];
    KeGets(str);
    KePrintK("\n");
    KePrintK(str);
        
    while(1);

    return;
}
