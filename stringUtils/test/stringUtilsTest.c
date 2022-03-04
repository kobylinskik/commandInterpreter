#include "stringUtils.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}

void tearDown(void) {}

void shouldCopyString(void) {
    char * originString = "test123";
    char targetString[20];
    uint8_t maxSize = 20;

    strCopy(originString, targetString, maxSize);

    TEST_ASSERT_EQUAL_STRING(originString, targetString);
}

void shouldWriteMessageWithParamsToBuffer(void) {
    char * message = "test %s test %s test %s test %s test";
    uint8_t inputLength = 11;
    char commandLabel[7];
    uint8_t argc = 0;

    char argv[MAX_ARGS][MAX_ARG_LENGTH];

    strCopy("first", argv[0], MAX_ARG_LENGTH);
    strCopy("second", argv[1], MAX_ARG_LENGTH);
    strCopy("third", argv[2], MAX_ARG_LENGTH);
    strCopy("fourth", argv[3], MAX_ARG_LENGTH);

    char buffer[100];
    uint8_t bufferSize = 100;

    writeMessageToBuffer(message, argv, buffer, bufferSize);

    TEST_ASSERT_EQUAL_STRING("test first test second test third test fourth test", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(shouldCopyString);
    RUN_TEST(shouldWriteMessageWithParamsToBuffer);
    return UNITY_END();
}
