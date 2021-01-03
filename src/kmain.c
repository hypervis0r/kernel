#include "common.h"
#include "kernel/io/video.h"
#include "kernel/io/input.h"
#include "kernel/interrupt.h"

void kmain(void)
{
    kstdout_init();     /* Initialize the stdout */
    kstdin_init();      /* Initialize the stdin  */
    idt_init();         /* Initialize the Interrupt Descriptor Table */
    pit_init(1000);     /* Initialize the PIT timer to tick every 1000 hz / 1ms */

    /* TODO: Add bit manipulation and defines for better readability */
    kstdout->attrib = 0x4F; /* Set background color to red, and foreground to white */

    KePrintK("Waiting for 2 seconds...\n");
    KeSleep(2000); /* Sleep for 2 seconds (to demonstrate PIT timer) */

    KeClearScreen(kstdout->attrib);
    KePrintK("TEST Enter keyboard input:\n");

    /* Get input from the PS/2 keyboard and display on screen */
    char str[50];
    KeGets(str);
    KePrintK("\n");
    KePrintK(str);
        
    while(1); /* go into infinite looooooop */

    return;
}
