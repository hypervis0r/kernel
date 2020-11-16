#include "input.h"

void kstdin_init(void)
{
    kstdin.buffer[0] = 0;
    kstdin.size = 1000;
}

int KeGets(char* buf)
{
    kb_enable();
    while(keyboard_status != ENTER_KEY_CODE);
    keyboard_status = NULL;
    mask_disable();
    
    KePrintK("KB Disabled\n");
    KePrintK(kstdin.buffer);

    strcpy(buf, kstdin.buffer); // TODO: Use safer alternative lol
    return 0;
}
