#include "video.h"

void kstdout_init(void)
{
    kstdout->base = (char*)0xb8000; // Starting address for video memory
    kstdout->max_x = (80*2); // 80 columns * 2 bytes per char
    kstdout->max_y = 25; // 25 rows
    kstdout->cur_x = 0;
    kstdout->cur_y = 0;
    kstdout->attrib = 0x0F;
}

int KeClearScreen(BYTE attrib)
{   
    /* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while (kstdout->cur_y < kstdout->max_y)
    {
        while (kstdout->cur_x < kstdout->max_x) 
        {
            int pos = (kstdout->cur_x + (kstdout->cur_y * kstdout->max_x));
		    
            /* blank character */
		    kstdout->base[pos] = ' ';
		    
            /* attribute-byte */
		    kstdout->base[pos + 1] = attrib; 		
		    
            kstdout->cur_x = kstdout->cur_x + 2;
	    }
        kstdout->cur_x = 0;
        kstdout->cur_y = kstdout->cur_y + 1;
    }
        
    kstdout->cur_x = 0;
    kstdout->cur_y = 0;

    return 0;
}

int KePutCharEx(const char chr, BYTE attrib, unsigned int pos_x, unsigned int pos_y)
{
    kstdout->cur_x = pos_x;
    kstdout->cur_y = pos_y;

    // New line
    if (kstdout->cur_x >= kstdout->max_x)
    {
        kstdout->cur_x = 0;
        kstdout->cur_y = kstdout->cur_y + 1;
    }
    else if (chr == '\n')
    {
        kstdout->cur_x = 0;
        kstdout->cur_y = kstdout->cur_y + 1;
        return 0;
    }
    else if(chr == '\b')
    {
        KePutCharEx(' ', attrib, kstdout->cur_x-2, kstdout->cur_y);
        kstdout->cur_x = kstdout->cur_x - 2;
        return 0;
    }

    int pos = (kstdout->cur_x + (kstdout->cur_y * kstdout->max_x));

    /* the character's ascii */
    kstdout->base[pos] = chr;
    /* attribute-byte */
    kstdout->base[pos+1] = attrib;
        
    kstdout->cur_x = kstdout->cur_x + 2;

    return 0;
}

int KePutChar(const char chr)
{
    return KePutCharEx(chr, kstdout->attrib, kstdout->cur_x, kstdout->cur_y);
}

int KePrintKEx(const char* str, BYTE attrib, unsigned int pos_x, unsigned int pos_y)
{    
    kstdout->cur_x = pos_x;
    kstdout->cur_y = pos_y;

    unsigned int j = 0;

    /* this loop writes the string to video memory */
    while (str[j] != '\0') 
    { 
        KePutCharEx(str[j], attrib, kstdout->cur_x, kstdout->cur_y); 
	    ++j;
    }
    return 0;
}

int KePrintK(const char* str)
{
    return KePrintKEx(str, kstdout->attrib, kstdout->cur_x, kstdout->cur_y);
}
