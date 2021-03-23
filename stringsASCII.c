#include "stringsASCII.h"
#include "errors.h"

void* getStringASCII()
{
    char buffer[81] = {0};
    void *res       = NULL;
    int len         = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buffer);
        if (n < 0)
        {
            if (!res)
            {
                return NULL;
            }
        }
        else if (n > 0)
        {
            int chunk_len   = (int)strlen(buffer);
            int str_len     = len + chunk_len;
            res             = realloc(res, str_len + 1);
            memcpy(res + len, buffer, chunk_len);

            len             = str_len;
        }
        else
        {
            scanf("%*c");
            n = 0;
        }
    } while (n > 0);

    if (len > 0)
    {
        *(char*)(res + len) = '\0';
    }
    else
    {
        res = calloc(1, sizeof(char));
    }

    return (void*)res;
}

char* UnSensCaseStrStrASCII(char* stringWhereFind, char* stringToFind)                                      //  This function finds substring without case sensitive and
{                                                                                                           //  returns pointer to the first symbol of it in the stringWhereToFind
    int64_t lengthOfStringWhereFind = strlen(stringWhereFind);
    int64_t lengthOfStringToFind    = strlen(stringToFind);

    int count           = 0;
    char* retPointer    = NULL;

    char upperCaseChar;
    char lowerCaseChar;

    for (int i = 0, k; i < lengthOfStringWhereFind; i++)
    {
        k = i;
        for (int j = 0; j < lengthOfStringToFind; j++)
        {
            upperCaseChar = lowerCaseChar = stringWhereFind[k];
            if ( isupper(stringWhereFind[k]) )
            {
                lowerCaseChar   = (char)tolower(stringWhereFind[k]);
            }
            if ( islower(stringWhereFind[k]) )
            {
                upperCaseChar   = (char)toupper(stringWhereFind[k]);
            }

            if (
                    lowerCaseChar == stringToFind[j]    ||
                    upperCaseChar == stringToFind[j]
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
            k++;
        }

        if (count == lengthOfStringToFind)
        {
            retPointer = stringWhereFind + i - count + 1;
            break;
        }
    }

    return retPointer;
}

int64_t lengthOfASCII(String* this)
{
    if (this->signature != UNIQSIG)
    {
        errorHandler(SIGNATURE_ERR);
        return -1;
    }
    return (int64_t)strlen(this->string);

}

void printASCII(String* this) {
    if (this->signature != UNIQSIG)
    {
        errorHandler(SIGNATURE_ERR);
        return;
    }
    if (this->encoding != ASCII)
    {
        errorHandler(ENCODING_ERR);
        return;
    }
    printf("%s\n", (char* )(this->string));
}

void concatASCII(String* this, String* source)
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
            (this->encoding != ASCII) &&
            (source->encoding != ASCII)
       )
    {
        errorHandler(ENCODING_ERR);
        return;
    }

    int64_t thisLength      = this->length(this);
    int64_t sourceLength    = source->length(source);

    this->string = realloc(this->string, sourceLength + thisLength + 1);
    if (this->string == NULL)
    {
        errorHandler(MEMORY_ALLOC_ERR);
        return;
    }

    strcat(this->string, source->string);
}

String* getSubStringASCII(String* this, int64_t startIndex, int64_t endIndex)
{
    if (this->signature != UNIQSIG)
    {
        errorHandler(SIGNATURE_ERR);
        return NULL;
    }
    if (this->encoding != ASCII)
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

    int64_t retLength = endIndex - startIndex;
    char*   tmpString = (char*) malloc(retLength + 1);

    if (tmpString == NULL)
    {
        errorHandler(MEMORY_ALLOC_ERR);
        return NULL;
    }

    tmpString[0] = '\0';
    strncat(tmpString, this->string + startIndex, retLength+1);
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

Bool findSubStringForASCII(String* this, String* source, Bool CaseSenseBool)
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
            (this->encoding != ASCII) &&
            (source->encoding != ASCII)
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
        if ( strstr((char*)this->string, (char*)source->string) != NULL )
        {
            return True;
        }
    }
    else
    {
        if ( UnSensCaseStrStrASCII((char*)this->string, (char*)source->string) != NULL)
        {
            return True;
        }
    }

    return False;
}
