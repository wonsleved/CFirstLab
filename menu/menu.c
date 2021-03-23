#include "menu.h"

void mainMenu() {
    setlocale(LC_ALL, "");
    int8_t statement = 1;
    do {
        int8_t enc;
        String* main;
        Encoding encoding;
        void* (*scanFunction)();
        printf("Choose encoding: \n");
        getOption(&enc, 1, 2, "1.\tASCII\n2.\tUTF\n");
        switch (enc) {
            case 1: {
                scanFunction = getStringASCII;
                encoding = ASCII;
                break;
            }
            case 2: {
                scanFunction = getStringUTF;
                encoding = UTF8;
                break;
            }
            default: {
                fprintf(stderr, "Chose another encoding!\n");
                continue;
            }
        }

        printf("Enter main string: ");
        void* str = scanFunction();
        if (str == NULL) break;
        main = createString(str, encoding);
        free(str);

        int8_t statementInner = 1;

        do {
            int8_t choice;
            getOption(&choice, 1, 7, MENU);
            switch (choice) {
                case 1: {
                    printf("Enter second string: ");
                    str= scanFunction();
                    String* second  = createString(str, encoding);
                    free(str);
                    main->concat(main, second);
                    printf("Result: ");
                    main->print(main);
                    deleteString(&second);
                    break;
                }
                case 2: {
                    int startIndex, endIndex;
                    printf("Enter start index: ");
                    scanf("%d", &startIndex);
                    printf("Enter end index: ");
                    scanf("%d", &endIndex);

                    String* subSTR = main->getSubString(main, startIndex, endIndex);

                    printf("Your sub string: ");
                    subSTR->print(subSTR);

                    int8_t replaceOpt;
                    printf("Do you want to replace main string with this one?\n");
                    getOption(&replaceOpt, 1, 2, "1.\tYES\n2.\tNO\n");
                    if (replaceOpt == 1) {
                        deleteString(&main);
                        main = subSTR;
                    } else {
                        deleteString(&subSTR);
                    }

                    break;
                }
                case 3: {
                    int8_t CaseSense;
                    Bool isCaseSense;
                    printf("Choose: \n");
                    getOption(&CaseSense, 1, 2, "1.\tCase sensetive\n2.\tCase INsensetive\n");
                    switch (CaseSense) {
                        case 1: {
                            isCaseSense = True;
                            break;
                        }
                        case 2: {
                            isCaseSense = False;
                            break;
                        }
                    }
                    printf("Enter second string to find: ");
                    void* newStr    = scanFunction();
                    String* second  = createString(newStr, encoding);
                    free(newStr);

                    printf("Main string %s second string with case %s option.\n",
                           main->findSubString(main, second, isCaseSense) ? "CONTAINS" : "DOES NOT CONTAIN",
                           isCaseSense ? "sensitive" : "INsensitive");
                    break;
                }
                case 4: {
                    printf("Length of the string is %ld symbols\n", main->length(main));
                    break;
                }
                case 5: {
                    printf("String:\t");
                    main->print(main);
                    break;
                }
                case 6: {
                    statementInner = 0;
                    break;
                }
                case 7: {
                    statementInner = 0;
                    statement = 0;
                    break;
                }
                default: {
                    fprintf(stderr, "This fucntion does not exist. Try again!\n");
                    break;
                }
            }
        } while (statementInner);

        if (!statement) deleteString(&main);


    } while (statement);




}

int8_t getOption(int8_t* name, int8_t start, int8_t end, char* opts) {
    char opt[2] = {0};
    do {
        printf("%s", opts);
        scanf("%s", opt);
        if (strlen(opt) == 0) {
            exit(EXIT_SUCCESS);
        }
        else if (opt[1] != '\0') {
            fprintf(stderr, "There is no this option, try another.\n");
        } else if( (opt[0] < (char)start + '0') || (opt[0] > (char)end + '0') ) {
            fprintf(stderr, "There is no this option, try another.\n");
        } else {
            *name = (int8_t)(opt[0] - '0');
            getchar();
            return 1;
        }
    } while (1);
}