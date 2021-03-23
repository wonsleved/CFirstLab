#include "tests.h"

//      ASCII

char* mainStringsTestsASCII[] =
        {
                "This is first test string!",
                "And here is second.",
                "It is third, as you see.",
                "If you are able to count to 4, you might know that it is forth.",
                "No way! One more, it is fifth now!",
                "Oh my god, incredible. This is the last one, sixth string.",
                "\0"
        };

char* ConcatStringsASCII[] =
        {
                "Add some fun!",
                "Good. Really good.",
                "Hah.",
                "Nice work!",
                "Thank you, bro.",
                "Yes, it truly works!",
        };

char* ConcatResultsASCII[] =
        {
                "This is first test string!Add some fun!",
                "And here is second.Good. Really good.",
                "It is third, as you see.Hah.",
                "If you are able to count to 4, you might know that it is forth.Nice work!",
                "No way! One more, it is fifth now!Thank you, bro.",
                "Oh my god, incredible. This is the last one, sixth string.Yes, it truly works!",
        };

int getSubStringsIndexsASCII[][2] =
        {
                {0, 6},
                {0, 2},
                {0, 10},
                {0, 4},
                {0, 15},
                {0, 7}
        };

char* getSubStringsResultsASCII[] =
        {
                "This is",
                "And",
                "It is third",
                "If yo",
                "No way! One more",
                "Oh my go",
        };

char* findSubStringsTestsASCII[] =
        {
                "s is first",
                "d here isn't sec",
                "s THiRd, As yO",
                "count to 4, you",
                "No way! One more, it is fifth now!",
                "gOd, INCREDIBLE. ThiS iS tHe lAst",
        };

Bool findSubStringsResultsASCIIsense[] =
        {
                True,
                False,
                False,
                True,
                True,
                False,
        };

Bool findSubStringsResultsASCIIinsense[] =
        {
                True,
                False,
                True,
                True,
                True,
                True,
        };

int lengthStringsResultsASCII[] =
        {
                26,
                19,
                24,
                63,
                34,
                58,
        };

//          UTF8

wchar_t* mainStringsTestsUTF8[] =
        {
                L"This i★s first test string!",
                L"And here is second.",
                L"It i✐ third, Αs you see.",
                L"If you are able to count to 4, you might know that it is forth.",
                L"Εν οιδα ",
                L"Oh my god, incredible. This is the last one, sixth string.",
                L"\0"
        };

wchar_t* ConcatStringsUTF8[] =
        {
                L"Add some fun!",
                L"Good. Really good.",
                L"Hah☭",
                L"Nice work!",
                L"οτι ουδεν οιδα.",
                L"Yes, it truly works!",
        };

wchar_t* ConcatResultsUTF8[] =
        {
                L"This i★s first test string!Add some fun!",
                L"And here is second.Good. Really good.",
                L"It i✐ third, Αs you see.Hah☭",
                L"If you are able to count to 4, you might know that it is forth.Nice work!",
                L"Εν οιδα οτι ουδεν οιδα.",
                L"Oh my god, incredible. This is the last one, sixth string.Yes, it truly works!",
        };

int getSubStringsIndexsUTF8[][2] =
        {
                {0, 6},
                {0, 2},
                {0, 10},
                {0, 4},
                {2, 5},
                {0, 7}
        };

wchar_t* getSubStringsResultsUTF8[] =
        {
                L"This i★",
                L"And",
                L"It i✐ third",
                L"If yo",
                L" οιδ",
                L"Oh my go",
        };

wchar_t* findSubStringsTestsUTF8[] =
        {
                L"s i★s first",
                L"d here isn't sec",
                L"✐ THiRd, αs yO",
                L"count to 4, you",
                L"ν ΟιΔα",
                L"gOd, INCREDIBLE. ThiS iS tHe lAst",
        };

Bool findSubStringsResultsUTF8sense[] =
        {
                True,
                False,
                False,
                True,
                False,
                False,
        };

Bool findSubStringsResultsUTF8insense[] =
        {
                True,
                False,
                True,
                True,
                True,
                True,
        };

int lengthStringsResultsUTF8[] =
        {
                27,
                19,
                24,
                63,
                8,
                58,
        };



void simpleTests() {
    printf("Start testing...\n");
    int ASCIItests  = 0;
    int UTF8tests   = 0;
    while (mainStringsTestsASCII[ASCIItests][0] != '\0') {
        ASCIItests++;
    }
    while (mainStringsTestsUTF8[UTF8tests][0] != (wchar_t)'\0') {
        UTF8tests++;
    }
    int allTests    = (ASCIItests + UTF8tests) * 5;

    int TestsNow    = 1;
    String* testStr;
    String* additStr;

    printf("\nTesting ASCII...\n\n");
    printf("Concatenation\n");
    for (int i = 0; i < ASCIItests; i++, TestsNow++) {
        testStr     = createString(mainStringsTestsASCII[i], ASCII);
        additStr    = createString(ConcatStringsASCII[i], ASCII);
        testStr->concat(testStr, additStr);

        if(strcmp((char*)testStr->string, ConcatResultsASCII[i])) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Getting sub strings\n");
    for (int i = 0; i < ASCIItests; i++, TestsNow++) {
        testStr     = createString(mainStringsTestsASCII[i], ASCII);
        additStr    = testStr->getSubString(testStr, getSubStringsIndexsASCII[i][0], getSubStringsIndexsASCII[i][1]);


        if(strcmp((char*)additStr->string, getSubStringsResultsASCII[i])) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Finding sub strings with case sensitive\n");
    for (int i = 0; i < ASCIItests; i++, TestsNow++) {
        testStr     = createString(mainStringsTestsASCII[i], ASCII);
        additStr    = createString(findSubStringsTestsASCII[i], ASCII);

        if(testStr->findSubString(testStr, additStr, True) != findSubStringsResultsASCIIsense[i]) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Finding sub strings withOUT case sensitive\n");
    for (int i = 0; i < ASCIItests; i++, TestsNow++) {
        testStr     = createString(mainStringsTestsASCII[i], ASCII);
        additStr    = createString(findSubStringsTestsASCII[i], ASCII);

        if(testStr->findSubString(testStr, additStr, False) != findSubStringsResultsASCIIinsense[i]) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Calculating the length of the string\n");
    for (int i = 0; i < ASCIItests; i++, TestsNow++) {
        testStr     = createString(mainStringsTestsASCII[i], ASCII);



        if(testStr->length(testStr) != lengthStringsResultsASCII[i]) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&testStr);
    }

    //      UTF8

    printf("\nTesting UTF8...\n\n");
    void* UTF8Str;
    printf("Concatenation\n");
    for (int i = 0; i < UTF8tests; i++, TestsNow++) {
        UTF8Str = malloc(wcslen(mainStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(mainStringsTestsUTF8[i])  * 4, mainStringsTestsUTF8[i], -1);
        testStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        UTF8Str = malloc(wcslen(ConcatStringsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(ConcatStringsUTF8[i]) * 4, ConcatStringsUTF8[i], -1);
        additStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        testStr->concat(testStr, additStr);

        UTF8Str = malloc(wcslen(ConcatResultsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(ConcatResultsUTF8[i]) * 4, ConcatResultsUTF8[i], -1);

        if(strcmp((char*)testStr->string, UTF8Str)) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }
        free(UTF8Str);

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Getting sub strings\n");
    for (int i = 0; i < UTF8tests; i++, TestsNow++) {

        UTF8Str = malloc(wcslen(mainStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(mainStringsTestsUTF8[i]) * 4, mainStringsTestsUTF8[i], -1);
        testStr = createString(UTF8Str, UTF8);
        free(UTF8Str);


        additStr    = testStr->getSubString(testStr, getSubStringsIndexsUTF8[i][0], getSubStringsIndexsUTF8[i][1]);

        UTF8Str = malloc(wcslen(getSubStringsResultsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(getSubStringsResultsUTF8[i]) * 4, getSubStringsResultsUTF8[i], -1);

        if(strcmp(additStr->string, UTF8Str)) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        free(UTF8Str);

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Finding sub strings with case sensitive\n");
    for (int i = 0; i < UTF8tests; i++, TestsNow++) {
        UTF8Str = malloc(wcslen(mainStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(mainStringsTestsUTF8[i]) * 4, mainStringsTestsUTF8[i], -1);
        testStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        UTF8Str = malloc(wcslen(findSubStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(findSubStringsTestsUTF8[i]) * 4, findSubStringsTestsUTF8[i], -1);
        additStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        if(testStr->findSubString(testStr, additStr, True) != findSubStringsResultsUTF8sense[i]) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Finding sub strings withOUT case sensitive\n");
    for (int i = 0; i < UTF8tests; i++, TestsNow++) {
        UTF8Str = malloc(wcslen(mainStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(mainStringsTestsUTF8[i]) * 4, mainStringsTestsUTF8[i], -1);
        testStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        UTF8Str = malloc(wcslen(findSubStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(findSubStringsTestsUTF8[i]) * 4, findSubStringsTestsUTF8[i], -1);
        additStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        if(testStr->findSubString(testStr, additStr, False) != findSubStringsResultsUTF8insense[i]) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&additStr);
        deleteString(&testStr);
    }

    printf("Calculating the length of the string\n");
    for (int i = 0; i < UTF8tests; i++, TestsNow++) {
        UTF8Str = malloc(wcslen(mainStringsTestsUTF8[i]) * 4);
        wcharToUTF8(UTF8Str, wcslen(mainStringsTestsUTF8[i]) * 4, mainStringsTestsUTF8[i], -1);
        testStr = createString(UTF8Str, UTF8);
        free(UTF8Str);

        if(testStr->length(testStr) != lengthStringsResultsUTF8[i]) {
            fprintf(stderr, "[%d/%d] Failed!\n", TestsNow, allTests);
            exit(1);
        }

        printf("[%d/%d] OK!\n", TestsNow, allTests);

        deleteString(&testStr);
    }

    return;

}
