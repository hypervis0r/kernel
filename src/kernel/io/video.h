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

KSTDOUT kstdout[sizeof(KSTDOUT)];

void InitSTDOUT(void);
int KeClearScreen(BYTE attrib);
int KePrintKEx(
        const char* str, 
        BYTE attrib, 
        unsigned int pos_x, 
        unsigned int pos_y
);
int KePrintK(const char* str);

#endif
