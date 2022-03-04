#include "stringUtils.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}

void tearDown(void) {}

void shouldWriteMessageWithParamsToBuffer(void) {
    char * message = "test %s test %s test %s test %s test";
    uint8_t inputLength = 11;
    char commandLabel[7];
    uint8_t argc = 0;

    char * argv[4];
    argv[0] = "first";
    argv[1] = "second";
    argv[2] = "third";
    argv[3] = "fourth";

    char buffer[100];
    uint8_t bufferSize = 100;

    writeMessageToBuffer(message, argv, buffer, bufferSize);

    TEST_ASSERT_EQUAL_STRING("test first test second test third test fourth test", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(shouldWriteMessageWithParamsToBuffer);
    return UNITY_END();
}
