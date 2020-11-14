#ifndef _VIDEO_H
#define _VIDEO_H

#include "../common.h"

typedef struct _STDOUT {
    char* base;
    int max_x;
    int max_y;
    int cur_x;
    int cur_y;
} STDOUT, * PSTDOUT;

void InitSTDOUT(PSTDOUT sStdout);

int KeClearScreen(PSTDOUT vidptr, BYTE attrib);
int KePrintK(PSTDOUT vidptr, const char* str, BYTE attrib);

#endif
