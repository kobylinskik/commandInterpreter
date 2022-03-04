#include "validationUtils.h"
#include "unity.h"
#include <stdint.h>

void setUp(void) {}

void tearDown(void) {}

void shouldWriteErrorMessageToBuffer_whenThereAreTooFewArguments(void) {
    uint8_t argc = 2;
    uint8_t expectedArgc = 3;

    char responseBuffer[80];
    uint8_t responseBufferSize = 80;

    validateArgc(argc, expectedArgc, responseBuffer, responseBufferSize);

    TEST_ASSERT_EQUAL_STRING("Invalid number of arguments. Expected 3, received 2 arguments.", responseBuffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(shouldWriteErrorMessageToBuffer_whenThereAreTooFewArguments);
    return UNITY_END();
}
