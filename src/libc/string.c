#include "string.h"

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
