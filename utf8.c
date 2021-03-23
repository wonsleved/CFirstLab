#include "utf8.h"

static const wchar_t offsetsFromUTF8[6] = {
        0x00000000UL, 0x00003080UL, 0x000E2080UL,
        0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

static const char trailingBytesForUTF8[256] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

// srcsz == -1 means that string is 0-terminated
int wcharToUTF8(char* dest, int sz, const wchar_t* src, int srcsz)
{
    wchar_t ch;
    int     i           = 0;
    int     size        = 0;
    char*   dest_end    = dest + sz;

    while (srcsz < 0 ? src[i] != 0 : i < srcsz)
    {
        ch = src[i];
        if (ch < 0x80)
        {
            if (dest >= dest_end)
                return i;
            *dest++ = (char)ch;
            size++;
        }
        else if (ch < 0x800)
        {
            if (dest >= dest_end-1)
                return i;
            *dest++ = (char)((ch >> 6)      | 0xC0);
            *dest++ = (char)((ch & 0x3F)    | 0x80);
            size+=2;
        }
        else if (ch < 0x10000)
        {
            if (dest >= dest_end-2)
                return i;
            *dest++ =   (char)((ch >> 12)           | 0xE0);
            *dest++ =   (char)(((ch >> 6) & 0x3F)   | 0x80);
            *dest++ =   (char)((ch & 0x3F)          | 0x80);

            size += 3;
        }
        else if (ch < 0x110000)
        {
            if (dest >= dest_end-3)
                return i;
            *dest++ =   (char)((ch >> 18)           | 0xF0);
            *dest++ =   (char)(((ch >> 12) & 0x3F)  | 0x80);
            *dest++ =   (char)(((ch >> 6) & 0x3F)   | 0x80);
            *dest++ =   (char)((ch & 0x3F)          | 0x80);

            size += 4;
        }
        i++;
    }
    if (dest < dest_end)
        *dest = '\0';
    return size;
}

int printUTF8Symbol(void* src)
{
//    setlocale(LC_ALL, "");

    int     srcsz   = sizeOfUTF8String(src);
    int     sz      = 4*srcsz + 4;
    void*   src_end = src + srcsz;
    int     i       = 0;
    int     nb;
    wchar_t ch;

    while (i < sz-1)
    {
        nb = (int)trailingBytesForUTF8[*(unsigned char*)src];
        if (srcsz == -1)
        {
            if (*(char*)src == 0)
            {
                printf("%lc", 0);
                printf("%lc", '\n');
                return i;
            }
        }
        else
        {
            if (src + nb >= src_end)
            {
                printf("%lc", 0);
                printf("%lc", '\n');
                return i;
            }
        }
        ch = 0;
        switch (nb)
        {   /* these fall through deliberately */
            case 3: ch += *(unsigned char*)src++; ch <<= 6;
            case 2: ch += *(unsigned char*)src++; ch <<= 6;
            case 1: ch += *(unsigned char*)src++; ch <<= 6;
            case 0: ch += *(unsigned char*)src++;
        }
        ch -= offsetsFromUTF8[nb];

        printf("%lc", ch);
        i++;
    }

    printf("%lc", '\n');
    return i;
}

int lengthOfNextUTF8Symbol(void *s)
{
    return trailingBytesForUTF8[(unsigned int)*(unsigned char*)s] + 1;
}

int sizeOfUTF8String(void* str)
{
    int len = 0;

    while ( *(char*)(str + len) != '\0' )
    {
        len++;
    }
    return len;
}

wchar_t UTF8ToWcharSymbol(void* src) {
//    setlocale(LC_ALL, "");

    int     nb = trailingBytesForUTF8[*(unsigned char*)src];
    wchar_t ch = 0;

    switch (nb)
    {   /* these fall through deliberately */
        case 3: ch += *(unsigned char*)src++; ch <<= 6;
        case 2: ch += *(unsigned char*)src++; ch <<= 6;
        case 1: ch += *(unsigned char*)src++; ch <<= 6;
        case 0: ch += *(unsigned char*)src;
    }
    ch -= offsetsFromUTF8[nb];

    return ch;
}


