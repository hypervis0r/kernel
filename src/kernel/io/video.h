#ifndef _VIDEO_H
#define _VIDEO_H

#include "../../common.h"

typedef struct _KSTDOUT {
    char* base;
    unsigned int max_x;
    unsigned int max_y;
    unsigned int cur_x;
    unsigned int cur_y;
    BYTE attrib;
} KSTDOUT, * PKSTDOUT;

PKSTDOUT kstdout;

void kstdout_init(void);
int KeClearScreen(BYTE attrib);
int KePutChar(const char chr);
int KePutCharEx(
        const char chr, 
        BYTE attrib, 
        unsigned int pos_x, 
        unsigned int pos_y
);
int KePrintKEx(
        const char* str, 
        BYTE attrib, 
        unsigned int pos_x, 
        unsigned int pos_y
);
int KePrintK(const char* str);

#endif
