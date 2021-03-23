#ifndef CFIRSTLAB_UTF_H
#define CFIRSTLAB_UTF_H
#include "dependences.h"


/* returns length of next utf-8 symbol in bytes */
int lengthOfNextUTF8Symbol(void *s);

/* convert wide character to UTF-8 data */
int wcharToUTF8(char* dest, int sz, const wchar_t* src, int srcsz);

/* print UTF-8 data */
int printUTF8Symbol(void* src);

/* returns size of utf-8 string in bytes */
int sizeOfUTF8String(void* str);

/* convert UTF-8 symbol to wide character symbol*/
wchar_t UTF8ToWcharSymbol(void* src);

#endif