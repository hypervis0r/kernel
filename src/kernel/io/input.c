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
       
        char keycodestr[50];
        itoa(keycode, keycodestr, 10);

        KePrintK("Key pressed\n");
        KePrintK(keycodestr);

        key_pressed = KeGetLastKeyPressed(keycode);
        
        if (key_pressed == '\n')
        {
            KePrintK("Enter Key Pressed\n");
            break;
        }
        else if (key_pressed == NULL)
        {
            KePrintK("Key Pressed Null\n");
            KeSetLastKeycode(NULL);
        }
        else
        {
            KePutChar(key_pressed);
            
            KeSetLastKeycode(NULL);
        }
    }

    // Disable keyboard // TODO: Figure out how to do this without disabling all interrupts on PIC1
    mask_disable();

    kstdin.buffer[++(kstdin.size)] = 0;
    strcpy(buf, kstdin.buffer); // TODO: Use safer alternative lol
    return 0;
}
