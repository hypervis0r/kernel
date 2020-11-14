#include "video.h"

void InitSTDOUT(void)
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

int KePrintKEx(const char* str, BYTE attrib)
{    
    unsigned int j = 0;

    /* this loop writes the string to video memory */
    while (str[j] != '\0') 
    { 
        // New line
        if (kstdout->cur_x >= kstdout->max_x)
        {
            kstdout->cur_x = 0;
            kstdout->cur_y = kstdout->cur_y + 1;
        }
        else if (str[j] == '\n')
        {
            kstdout->cur_x = 0;
            kstdout->cur_y = kstdout->cur_y + 1;
            ++j;
            continue;
        }

		int pos = (kstdout->cur_x + (kstdout->cur_y * kstdout->max_x));

        /* the character's ascii */
		kstdout->base[pos] = str[j];
		/* attribute-byte */
	    kstdout->base[pos+1] = attrib;
		    
        ++j;
		kstdout->cur_x = kstdout->cur_x + 2;
	}
    
    return 0;
}

int KePrintK(const char* str)
{
    int iResult = 0;

    iResult = KePrintKEx(str, kstdout->attrib);
    return iResult;
}
