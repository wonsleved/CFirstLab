#ifndef CFIRSTLAB_ERRORS_H
#define CFIRSTLAB_ERRORS_H

#include "dependences.h"

typedef enum Error {
    ENCODING_ERR = 0,
    MEMORY_ALLOC_ERR = 1,
    SIGNATURE_ERR = 2,
    INDEX_ERR = 3,
    MEMORY_FREE_ERR = 4
} Error;

void errorHandler(Error error);

#endif
