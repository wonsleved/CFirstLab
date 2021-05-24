#include "strings.h"
#include "errors.h"
#include "stringsASCII.h"
#include "stringsUTF.h"

void deleteString(String** str) {
    if ((*str) == NULL)
    {
        errorHandler(MEMORY_FREE_ERR);
        return;
    }
    if ((*str)->signature != UNIQSIG)
    {
        errorHandler(SIGNATURE_ERR);
        return;
    }
    if ((*str)->string == NULL)
    {
        errorHandler(MEMORY_FREE_ERR);
        return;
    }

    free((*str)->string);
    free(*str);
    *str = NULL;
}



String* createString(void* str, Encoding encoding) {
    if ( (encoding != ASCII) && (encoding != UTF8))
    {
        errorHandler(ENCODING_ERR);
    }

    String* retString = (String*) malloc(sizeof(String));                               //  Memory allocation for new String
    if (retString == NULL)
    {                                                            //  In case memory was not allocated for String object
        errorHandler(MEMORY_ALLOC_ERR);
        return NULL;
    }

    int64_t stringSizeInBytes   = strlen((char*)str);                                   //  string contains null byte in its end therefore we can find its size
    (retString->string)         = malloc(stringSizeInBytes * sizeof(char));
    if (retString->string == NULL) {                                                    //  In case memory was not allocated for string in String object
        errorHandler(MEMORY_ALLOC_ERR);
        free(retString);
        return NULL;
    }
    memcpy(retString->string, str, stringSizeInBytes + 1);                           //  Copying passed string to string if String object | + 1 for null byte

    retString->signature    = UNIQSIG;                                                  //  When memory was successfully allocated signature must be assigned
    retString->encoding     = encoding;                                                 //  Setting retString encoding to encoding passed to function

    if (encoding == ASCII)
    {
        retString->print            = printASCII;
        retString->concat           = concatASCII;
        retString->length           = lengthOfASCII;
        retString->getSubString     = getSubStringASCII;
        retString->findSubString    = findSubStringForASCII;
    }
    else // encoding == UTF8
    {
        retString->print            = printUTF;
        retString->concat           = concatUTF;
        retString->length           = lengthOfUTF;
        retString->getSubString     = getSubStringUTF;
        retString->findSubString    = findSubStringForUTF;
    }

    return retString;
}