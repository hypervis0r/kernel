#include "input.h"

void kstdin_init(void)
{
    kstdin.buffer[0] = 0;
    kstdin.size = 0;
}

int KeGets(char* buf)
{
    unsigned char keycode = NULL;
    char key_pressed = NULL;

    // Clear kstdin
    memset(kstdin.buffer, 0, sizeof(kstdin.buffer));
    kstdin.size = 0;

    // Enable keyboard
    kb_enable();
    
    while(TRUE)
    {
        keycode = KeWaitForKeyPress();
        key_pressed = KeGetLastKeyPressed(keycode);
        
        if (key_pressed == '\n')
            break;
        else
        {
            kstdin.buffer[(kstdin.size)++] = key_pressed;

            KePutChar(key_pressed);      
            KeSetLastKeycode(NULL);
        }
    }

    // Disable keyboard // TODO: Figure out how to do this without disabling all interrupts on PIC1
    mask_disable();

    strcpy(buf, kstdin.buffer); // TODO: Use safer alternative lol
    return 0;
}
