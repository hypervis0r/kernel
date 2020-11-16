#ifndef _INPUT_H
#define _INPUT_H

#include "../../common.h"
#include "../interrupt.h"
#include "../../libc/string.h"

typedef struct _KSTDIN
{
    char buffer[1000]; // TODO: Replace this with a char*, and write an malloc() implementation.
    DWORD size;
} KSTDIN, * PKSTDIN;

KSTDIN kstdin;

void kstdin_init(void);
int KeGets(char* buf);


#endif
