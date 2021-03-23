#include "errors.h"

void errorHandler(Error error) {
    fprintf(stderr, "Something went wrong...\n");
    switch (error)
    {
        case (ENCODING_ERR):{
            fprintf(stderr, "Encoding error. Check your input or try again.\n");
            exit(EXIT_FAILURE);
        }
        case MEMORY_ALLOC_ERR: {
            fprintf(stderr, "Memory wasn't allocated. Try again.\n");
            exit(EXIT_FAILURE);
        }
        case SIGNATURE_ERR: {
            fprintf(stderr, "Signature error. Signatures doesn't match. It seems to be a memory corruption. Try again.\n");
            exit(EXIT_FAILURE);
        }
        case INDEX_ERR: {
            fprintf(stderr, "Index error. Indexes must be more than or equal to 0 and less than or equal to the length of the string. Try again.\n");
            exit(EXIT_FAILURE);
        }
        case MEMORY_FREE_ERR: {
            fprintf(stderr, "Memory free error. Cannot free memory, this string is already free.\n");
            exit(EXIT_FAILURE);
        }
        default: {
            fprintf(stderr, "Unknown error.\n");
            exit(EXIT_FAILURE);
        }
    }
}
