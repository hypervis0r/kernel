#include "keyboard.h"

BYTE keyboard_status = NULL;

/* The following array is taken from 
    http://www.osdever.net/bkerndev/Docs/keyboard.htm
   All credits where due
*/
BYTE keyboard_map[128] = {
    0,  27, 
    '1', '2', '3', '4', '5', '6', '7', '8',	'9', '0', 
    '-', '=', '\b',	/* Backspace */
    '\t',			/* Tab */
    'q', 'w', 'e', 'r',	't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
    '\n',	/* Enter key */
    0,		/* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   
    0,		/* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',	'm', ',', '.', '/',   
    0,		/* Right shift */
   '*',
    0,	    /* Alt */
    ' ',	/* Space bar */
    0,	    /* Caps lock */
    0,	    /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	    /* < ... F10 */
    0,	    /* 69 - Num lock*/
    0,	    /* Scroll Lock */
    0,	    /* Home key */
    0,	    /* Up Arrow */
    0,	    /* Page Up */
    '-',
    0,	    /* Left Arrow */
    0,
    0,	    /* Right Arrow */
    '+',
    0,	    /* 79 - End key*/
    0,	    /* Down Arrow */
    0,	    /* Page Down */
    0,	    /* Insert Key */
    0,	    /* Delete Key */
    0,   0,   0,
    0,	    /* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_handler_main(void)
{
	unsigned char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	keyboard_status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (keyboard_status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		
        if(keycode < 0)
			return;

        if(keycode == ENTER_KEY_CODE)
        {
            KePrintK("\nEnter key pressed\n");
            keyboard_status = keycode;
            return;
        }

        const char send[2] = {(char)keyboard_map[(int)keycode], 0};
        KePrintK(send);

        strcat(kstdin.buffer, send);
    }    
}
