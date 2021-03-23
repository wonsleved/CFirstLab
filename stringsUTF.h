#ifndef CFIRSTLAB_STRINGSUTF_H
#define CFIRSTLAB_STRINGSUTF_H

#include "dependences.h"
#include "strings.h"
#include "utf8.h"

void printUTF(String* this);
void concatUTF(String* this, String* source);


int64_t lengthOfUTF(String* this);
Bool    findSubStringForUTF(String* this, String* source, Bool  CaseSenseBool);
String* getSubStringUTF(String* this, int64_t startIndex, int64_t endIndex);


void* getStringUTF();
void* UnSensCaseStrStrUTF(String* stringWhereFind, String* stringToFind);


#endif //CFIRSTLAB_STRINGSUTF_H
