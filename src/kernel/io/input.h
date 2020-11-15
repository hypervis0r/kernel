#ifndef _INPUT_H
#define _INPUT_H

#include "../../common.h"

typedef struct _KSTDIN
{
    char *buffer;
    DWORD size;
} KSTDIN, * PKSTDIN;

int KeGets(char* buf, DWORD size);


#endif
