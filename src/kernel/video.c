#include "video.h"

void InitSTDOUT(PSTDOUT sStdout)
{
    sStdout->base = (char*)0xb8000; // Starting address for video memory
    sStdout->max_x = (80*2); // 80 columns * 2 bytes per char
    sStdout->max_y = 25; // 25 rows
    sStdout->cur_x = 0;
    sStdout->cur_y = 0;
}

int KeClearScreen(PSTDOUT vidptr, BYTE attrib)
{   
    /* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while (vidptr->cur_y < vidptr->max_y)
    {
        while (vidptr->cur_x < vidptr->max_x) 
        {
            int pos = (vidptr->cur_x + (vidptr->cur_y * vidptr->max_x));
		    
            /* blank character */
		    vidptr->base[pos] = ' ';
		    
            /* attribute-byte */
		    vidptr->base[pos + 1] = attrib; 		
		    
            vidptr->cur_x = vidptr->cur_x + 2;
	    }
        vidptr->cur_x = 0;
        vidptr->cur_y = vidptr->cur_y + 1;
    }
        
    vidptr->cur_x = 0;
    vidptr->cur_y = 0;

    return 0;
}

int KePrintK(PSTDOUT vidptr, const char* str, BYTE attrib)
{    
    unsigned int j = 0;

    /* this loop writes the string to video memory */
    while (str[j] != '\0') 
    { 
        // New line if out of line space
        if (vidptr->cur_x >= vidptr->max_x)
        {
            vidptr->cur_x = 0;
            vidptr->cur_y = vidptr->cur_y + 1;
        }

		int pos = (vidptr->cur_x + (vidptr->cur_y * vidptr->max_x));

        /* the character's ascii */
		vidptr->base[pos] = str[j];
		/* attribute-byte */
	    vidptr->base[pos+1] = attrib;
		    
        ++j;
		vidptr->cur_x = vidptr->cur_x + 2;
	}
    
    return 0;
}
