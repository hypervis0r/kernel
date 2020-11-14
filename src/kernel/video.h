#ifndef _VIDEO_H
#define _VIDEO_H

#include "../common.h"

typedef struct _KSTDOUT {
    char* base;
    int max_x;
    int max_y;
    int cur_x;
    int cur_y;
    BYTE attrib;
} KSTDOUT, * PKSTDOUT;

KSTDOUT kstdout[sizeof(KSTDOUT)];

void InitSTDOUT(void);
int KeClearScreen(BYTE attrib);
int KePrintKEx(const char* str, BYTE attrib);
int KePrintK(const char* str);

#endif
