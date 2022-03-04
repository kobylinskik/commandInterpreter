#include "command.h"
#include "unity.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID_NUMBER_OF_ARGUMENTS "Invalid number of arguments. Expected 4 arguments, received %s arguments"

void setUp(void) {}

void tearDown(void) {}

uint8_t validateArgcEqualsFour(uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize) {
    if (argc != 4) {
        char writeMessageArg[2] = {'0', '\0'};
        writeMessageArg[0] += argc;
        char * writeMessageArgs = (char *)writeMessageArg;
        writeMessageToBuffer(INVALID_NUMBER_OF_ARGUMENTS, &writeMessageArgs, responseBuffer, responseBufferSize);
        return 1;
    }
    return 0;
};

uint8_t testStringRet(uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize) {
    char * result = "result";
    while (*result != 0) {
        *(responseBuffer++) = *result++;
    }
    return 0;
}

uint8_t testCommandWithParamsFunction(uint8_t argc, char ** argv, char * result, uint8_t responseBufferSize) {
    char * charPtr = result;
    for (int i = 0; i < argc; i++) {
        for (int j = 0; argv[i][j] != 0; j++) {
            *(charPtr++) = argv[i][j];
        }
        *(charPtr++) = ' ';
    }
    *charPtr = 0;
    return 0;
}

void shouldExecuteCommand(void) {
    command_t command;
    command.function = *testStringRet;
    uint8_t argc = 0;
    char ** argv = NULL;
    char result[7];
    execute(&command, argc, argv, result, 7);
    TEST_ASSERT_EQUAL_STRING("result", result);
}

void shouldExecuteCommandWithParams(void) {
    command_t command;
    command.function = *testCommandWithParamsFunction;
    uint8_t argc = 3;
    char * arg0 = "test";
    char * arg1 = "result";
    char * arg2 = "number 1";
    char * argv[3];
    argv[0] = arg0;
    argv[1] = arg1;
    argv[2] = arg2;
    char result[22];
    execute(&command, argc, argv, result, 22);
    TEST_ASSERT_EQUAL_STRING("test result number 1 ", result);
}

void shouldValidateCommandParams(void) {
    char * commandName = "testCommand";

    command_t command;
    command.label = commandName;
    command.validation = *validateArgcEqualsFour;

    uint8_t argc = 2;
    char * argv[2];
    argv[0] = "testParam";
    argv[1] = "test2";

    char responseBuffer[72];
    uint8_t responseBufferSize = 72u;

    uint8_t result = validateParams(&command, argc, argv, responseBuffer, responseBufferSize);
    TEST_ASSERT_EQUAL_UINT8(1, result);
    TEST_ASSERT_EQUAL_STRING("Invalid number of arguments. Expected 4 arguments, received 2 arguments", responseBuffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(shouldExecuteCommand);
    RUN_TEST(shouldExecuteCommandWithParams);
    RUN_TEST(shouldValidateCommandParams);
    return UNITY_END();
}
