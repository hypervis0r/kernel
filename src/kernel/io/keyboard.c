#include "keyboard.h"

static unsigned char keycode = NULL;





/* Every time a key on a PS/2 keyboard is pressed,
 * it raises IRQ1, which we handle using this function */
void keyboard_handler_main(void)
{
    BYTE keyboard_status = NULL;
    BYTE scancode = NULL;

    /* write EOI */
	write_port(0x20, 0x20);

	keyboard_status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (keyboard_status & 0x01) 
    {
		scancode = read_port(KEYBOARD_DATA_PORT);
		
        if(scancode < 0)
            keycode = NULL;

        if((scancode & 128) == 128)
            keycode = NULL; // Released // TODO: Idk what to do here yet, so :/
        else
            keycode = scancode; // Pressed
    }    
}

/* Blocks program runtime until a key is pressed.
 * IDK if I should set keycode to NULL after we get 
 * input, so I'll just have to figure that out l8r */
unsigned char KeWaitForKeyPress(void)
{
    while(TRUE)
    {
        if (keycode != NULL)
            return keycode;
    }
}

char KeGetLastKeyPressed(unsigned char src)
{
	/* The following array is taken from 
	http://www.osdever.net/bkerndev/Docs/keyboard.htm
	All credits where due
	*/

	/* Keyboard map, take scancode and grab the 
	* value at the index.
	* TODO: figure out a way to interchange this 
	* Also TODO: NOT HAVE IT IN A FUCKING FUNCTION THIS IS 
	* SO FUCKING STUPID */
	BYTE keyboard_map[128] = {
	0,  27, 
	'1', '2', '3', '4', '5', '6', '7', '8',	'9', '0', 
	'-', '=', '\b',	/* Backspace */
	'\t',		/* Tab */
	'q', 'w', 'e', 'r',	't', 'y', 'u', 'i', 'o', 'p', '[', ']', 
	'\n',		/* Enter key */
	0,		/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   
	0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',	'm', ',', '.', '/',   
	0,		/* Right shift */
	'*',
	0,	    	/* Alt */
	' ',		/* Space bar */
	0,	    	/* Caps lock */
	0,	    	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	    	/* < ... F10 */
	0,	    	/* 69 - Num lock*/
	0,	    	/* Scroll Lock */
	0,	    	/* Home key */
	0,	    	/* Up Arrow */
	0,	    	/* Page Up */
	'-',
	0,	    	/* Left Arrow */
	0,
	0,	    	/* Right Arrow */
	'+',
	0,	    	/* 79 - End key*/
	0,	    	/* Down Arrow */
	0,	    	/* Page Down */
	0,	    	/* Insert Key */
	0,	    	/* Delete Key */
	0,   0,   0,
	0,	    	/* F11 Key */
	0,		/* F12 Key */
	0,		/* All other keys are undefined */
	};

	BYTE key_pressed = keyboard_map[src];

	return key_pressed;
}

unsigned char KeGetLastKeycode(void)
{
    return keycode;
}

void KeSetLastKeycode(unsigned char src)
{
    keycode = src;
}
