#ifndef CFIRSTLAB_MENU_H
#define CFIRSTLAB_MENU_H

#include "../strings.h"
#include "../stringsUTF.h"
#include "../stringsASCII.h"

#define MENU                    \
"1.\tConcatenate strings\n"     \
"2.\tGet sub string\n"          \
"3.\tFind sub string\n"         \
"4.\tGet the length of the string\n"    \
"5.\tPrint the stirng\n"            \
"6.\tClear the string\n"            \
"7.\tExit\n"                    \

void mainMenu();
int8_t getOption(int8_t*, int8_t, int8_t, char* opts);

#endif //CFIRSTLAB_MENU_H
