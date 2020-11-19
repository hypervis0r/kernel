#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H

#include "../common.h"

void *memcpy(void *dest, const void *src, SIZE_T len);
void *memset(void *dest, int val, SIZE_T len);

char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, SIZE_T size);
SIZE_T strlen(const char* src);
SIZE_T strnlen(const char* src, SIZE_T maxlen);

char *itoa(int value, char *result, int base); 

#endif
