#ifndef LAB_STRINGS_H
#define LAB_STRINGS_H

#include "dependences.h"

#define UNIQSIG 0xf12345f

typedef enum Encoding {
    ASCII,
    UTF8,
} Encoding;

typedef enum Bool {
    False   = 0,    // isn`t case sensitive
    True    = 1,    // is case sensitive
} Bool;

//
//  Defining main module
//

typedef struct String {

    //
    //  Properties
    //

    int64_t         signature;
    Encoding        encoding;
    void*           string;

    //
    //  Methods
    //

    void            (*print)(   struct String* this);
    void            (*concat)(  struct String* this,
                                struct String* source);

    struct String*  (*getSubString)(struct String* this,
                                    int64_t startIndex,
                                    int64_t endIndex);

    int64_t         (*length)(struct String* this);
    Bool            (*findSubString)(   struct  String* this,
                                        struct  String* source,
                                        Bool    CaseSensBool);

} String;


String* createString(void* str, Encoding encoding);
void    deleteString(String** str);

#endif
