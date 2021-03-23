#include "stringsUTF.h"
#include "errors.h"

void* getStringUTF()
{
    wchar_t buffer[81]  = {0};
    int8_t wCharSize    = sizeof(wchar_t);
    char *res           = (char*) malloc(sizeof(char));
    int lenInBytes      = 0;
    int n;
    int len = 0;
    do {
        scanf("%80l[^\n]", buffer);
        if (buffer[len-1] == L'\n')
        {
            buffer[len-1] = L'\0';
            len--;
        }

        if (len < 80)
        {
            n = 1;
        }
        else
        {
            n = 2;
        }

        if (n < 0)
        {
            if (!res)
            {
                free(res);
                return NULL;
            }
        }
        else if (n > 0)
        {
            int chunkLenInBytes = (int)wcslen(buffer) * wCharSize;
            int strLenInBytes   = lenInBytes + chunkLenInBytes;
            res                 = (char*) realloc(res, strLenInBytes + 1);
            int size            = wcharToUTF8(res + lenInBytes, chunkLenInBytes + 1, buffer,
                                              chunkLenInBytes / wCharSize);
            lenInBytes          = strLenInBytes - chunkLenInBytes + size;
            res                 = (char*) realloc(res, lenInBytes + 1);
        }
        else
        {
            wscanf(L"%*c");
            n = 0;
        }
        n--;
    } while (n > 0);

    if (lenInBytes > 0)
    {
        res[lenInBytes] = '\0';
    }
    else
    {
        res = calloc(1, wCharSize);
    }
    getchar();
    return (void*)res;
}







void printUTF(String* this)
{
    if (this->signature != UNIQSIG)
    {
        errorHandler(SIGNATURE_ERR);
        return;
    }
    if (this->encoding != UTF8)
    {
        errorHandler(ENCODING_ERR);
        return;
    }
    printUTF8Symbol(this->string);
}




void concatUTF(String* this, String* source)
{
    if (
            (this->signature != UNIQSIG) ||
            (source->signature != UNIQSIG)
       )
    {
        errorHandler(SIGNATURE_ERR);
        return;
    }
    if (
            (this->encoding != UTF8) &&
            (source->encoding != UTF8)
       )
    {
        errorHandler(ENCODING_ERR);
        return;
    }

    int64_t thisSize        = sizeOfUTF8String(this->string);
    int64_t sourceSize      = sizeOfUTF8String(source->string);

    this->string            = realloc(this->string, sourceSize + thisSize + 1);
    if (this->string == NULL)
    {
        errorHandler(MEMORY_ALLOC_ERR);
        return;
    }
    memcpy(this->string + thisSize, source->string, sourceSize + 1);
}


int64_t lengthOfUTF(String* this)
{
    int64_t length  = 0;
    void* symbol    = (this->string);

    while ( *(char*)symbol != '\0' )
    {
        length++;
        symbol += lengthOfNextUTF8Symbol(symbol);
    }

    return length;
}


String* getSubStringUTF(String* this, int64_t startIndex, int64_t endIndex)
{
    if (this->signature != UNIQSIG)
    {
        errorHandler(SIGNATURE_ERR);
        return NULL;
    }
    if (this->encoding != UTF8)
    {
        errorHandler(ENCODING_ERR);
        return NULL;
    }

    int64_t length = this->length(this);
    if (
            (startIndex < 0)    ||
            (endIndex > length) ||
            (startIndex >= endIndex)
       )
    {
        errorHandler(INDEX_ERR);
        return NULL;
    }

    int64_t startByte   = 0;
    int64_t endByte     = 0;
    for (int i = 0; i < length; i++)
    {
        if (i < startIndex)
        {
            startByte += lengthOfNextUTF8Symbol(this->string + startByte);
        }
        if (i <= endIndex)
        {
            endByte += lengthOfNextUTF8Symbol(this->string + endByte);
        }
    }
    endByte--;

    int64_t retSize = endByte - startByte;
    void*   tmpString = malloc(retSize + 1);

    if (tmpString == NULL)
    {
        errorHandler(MEMORY_ALLOC_ERR);
        return NULL;
    }

    memcpy(tmpString, this->string + startByte, retSize + lengthOfNextUTF8Symbol(this->string + endByte));
    *(char*)(tmpString + retSize + 1) = '\0';

    Encoding    retEncoding = this->encoding;
    String*     retString   = createString(tmpString, retEncoding);

    if (retString == NULL)
    {
        free(tmpString);
        return NULL;
    }

    free(tmpString);

    return retString;
}




Bool    findSubStringForUTF(String* this, String* source, Bool  CaseSenseBool)
{
    if (
            (this->signature != UNIQSIG) ||
            (source->signature != UNIQSIG)
       )
    {
        errorHandler(SIGNATURE_ERR);
        return False;
    }
    if (
            (this->encoding != UTF8) &&
            (source->encoding != UTF8)
       )
    {
        errorHandler(ENCODING_ERR);
        return False;
    }

    int64_t thisLength      = this->length(this);
    int64_t sourceLength    = source->length(source);

    if (thisLength < sourceLength) return False;

    if (CaseSenseBool)
    {
        if ( strstr((char*)this->string, (char*)source->string) != NULL )       //  This function works well with unicode
        {
            return True;
        }
    }
    else
    {
        if ( UnSensCaseStrStrUTF(this, source) != NULL)
        {
            return True;
        }
    }

    return False;
}

void* UnSensCaseStrStrUTF(String* stringWhereFind, String* stringToFind)
{
    setlocale(LC_ALL, ""); // for debug
    int64_t sizeOfStringWhereFind = sizeOfUTF8String(stringWhereFind->string);
    int64_t sizeOfStringToFind    = sizeOfUTF8String(stringToFind->string);

    int64_t lengthOfStringToFind  = stringToFind->length(stringToFind);

    int count           = 0;
    void* retPointer    = NULL;

    wchar_t upperCaseChar;
    wchar_t lowerCaseChar;


    for (int i = 0, k; i < sizeOfStringWhereFind; i += lengthOfNextUTF8Symbol(stringWhereFind->string + i))
    {
        k = i;
        for (int j = 0; j < sizeOfStringToFind; j += lengthOfNextUTF8Symbol(stringToFind->string + j))
        {
            wchar_t ch = UTF8ToWcharSymbol(stringWhereFind->string + k);
            upperCaseChar = lowerCaseChar = ch;
            if ( iswupper(ch) )
            {
                lowerCaseChar = towlower(ch);

            }
            else if ( iswlower(ch) )
            {
                upperCaseChar = towupper(ch);
            }
            if (
                    lowerCaseChar == UTF8ToWcharSymbol(stringToFind->string + j) ||
                            upperCaseChar == UTF8ToWcharSymbol(stringToFind->string + j)
               )
            {
                count++;
            }
            else
            {
                count = 0;
                break;
            }
            if (count == lengthOfStringToFind) break;
            k += lengthOfNextUTF8Symbol(stringWhereFind->string + k);
        }

        if (count == lengthOfStringToFind)
        {
            retPointer  = stringWhereFind->string + i - count;
            retPointer += lengthOfNextUTF8Symbol(retPointer);
            break;
        }
    }

    return retPointer;
}