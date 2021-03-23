#ifndef CFIRSTLAB_STRINGSASCII_H
#define CFIRSTLAB_STRINGSASCII_H

#include "strings.h"
#include "dependences.h"


void    printASCII(String* this);
void    concatASCII(String* this, String* source);

int64_t lengthOfASCII(String* this);
Bool    findSubStringForASCII(String* this, String* source, Bool  CaseSenseBool);
String* getSubStringASCII(String* this, int64_t startIndex, int64_t endIndex);


void* getStringASCII();

#endif
