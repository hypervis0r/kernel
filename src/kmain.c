#include "common.h"
#include "kernel/video.h"

void kmain(void)
{
    PSTDOUT vidptr = NULL;

    InitSTDOUT(vidptr);

    KeClearScreen(vidptr, (BYTE)0x4F);
    KePrintK(vidptr, "TEST", (BYTE)0x4F);
    
    return;
}
