#include "string.h"

void *memset(void *dest, int val, SIZE_T len)
{
    unsigned char *ptr = dest;
    while (len-- > 0)
        *ptr++ = val;
    return dest;
}

void *memcpy(void *dest, const void *src, SIZE_T len)
{
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}

char *strcpy(char *dest, const char *src)
{
    return memcpy(dest, src, strlen(src)+1);
}

char *strncat(char *dest, const char *src, SIZE_T size)
{
    char *s = dest;
    
    /* Find the end of S1.  */
    dest += strlen(dest);
    SIZE_T ss = strnlen(src, size);
    
    dest[ss] = '\0';
    memcpy(dest, src, ss);
    
    return s;
}

char *strcat(char *dest, const char *src)
{
    while (*dest) dest++;
    while (*dest++ = *src++);
    return --dest;    
}

SIZE_T strlen(const char* src)
{
    SIZE_T size = 0;
    while (src[size] != '\0')
        ++size;
    return size;
}

SIZE_T strnlen(const char* src, SIZE_T maxlen)
{
    SIZE_T size = 0;
    while(size < maxlen)
    {
        if (src[size] == '\0')
            break;
        else
            ++size;
    }
    
    return size;
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char *itoa(int value, char *result, int base) 
{
    // check that the base if valid
    if (base < 2 || base > 36) 
    { 
        *result = '\0'; 
        return result; 
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do 
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) 
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    return result;
}
