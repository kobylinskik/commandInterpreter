#include "inputHandler.h"
#include "unity.h"
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

uint8_t writeHelloToOuputBuffer(uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize) {
    char * message = "Hello";
    writeMessageToBuffer(message, 0, responseBuffer, responseBufferSize);
    return 0;
}

void shouldSplitInputIntoCommandLabelAndTwoParams(void) {
    char * input = "setPin(A,5)";
    uint8_t inputLength = 11;
    char commandLabel[7];
    uint8_t argc = 0;

    /*char * argv[2];
    argv[0] = malloc(2 * sizeof(char));
    argv[1] = malloc(2 * sizeof(char));*/

    char argv[MAX_ARGS][MAX_ARG_LENGTH];

    splitInputIntoCommandAndArgs(input, inputLength, commandLabel, &argc, argv);

    TEST_ASSERT_EQUAL_STRING("setPin", commandLabel);
    TEST_ASSERT_EQUAL_UINT8(2u, argc);
    TEST_ASSERT_EQUAL_STRING("A", argv[0]);
    TEST_ASSERT_EQUAL_STRING("5", argv[1]);
}

void shouldWriteNoCommandFoundToResponseBuffer_whenNoCommandIsFound(void) {
    char * commandName = "invalidCommand";
    uint8_t argc = 1;
    char * argv[1];
    argv[0] = "testParam";

    commandMap_t cmap;
    initMap(&cmap);

    char responseBuffer[37];
    uint8_t responseBufferSize = 37u;

    executeInput(&cmap, commandName, argc, argv, responseBuffer, responseBufferSize);

    TEST_ASSERT_EQUAL_STRING("Command 'invalidCommand' not found\n", responseBuffer);
}

void shouldWriteValidationErrorMessageToBuffer_onExecuteWithInvalidNumberOfArguments(void) {
    char * commandName = "testCommand";

    command_t command;
    command.label = commandName;
    command.validation = *validateArgcEqualsFour;

    uint8_t argc = 2;
    char * argv[2];
    argv[0] = "testParam";
    argv[1] = "test2";

    commandMap_t cmap;
    initMap(&cmap);

    put(&cmap, &command);

    char responseBuffer[75];
    uint8_t responseBufferSize = 75u;

    executeInput(&cmap, commandName, argc, argv, responseBuffer, responseBufferSize);

    TEST_ASSERT_EQUAL_STRING("Invalid number of arguments. Expected 4 arguments, received 2 arguments", responseBuffer);
}

void shouldWriteHelloToResponseBuffer_onInputExecution(void) {
    char * commandName = "testCommand";

    command_t command;
    command.label = commandName;
    command.validation = *validateArgcEqualsFour;
    command.function = *writeHelloToOuputBuffer;

    uint8_t argc = 4;
    char * argv[4];
    argv[0] = "testParam";
    argv[1] = "test2";
    argv[3] = "test3";
    argv[4] = "test4";

    commandMap_t cmap;
    initMap(&cmap);

    put(&cmap, &command);

    char responseBuffer[75];
    uint8_t responseBufferSize = 75u;

    executeInput(&cmap, commandName, argc, argv, responseBuffer, responseBufferSize);

    TEST_ASSERT_EQUAL_STRING("Hello", responseBuffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(shouldSplitInputIntoCommandLabelAndTwoParams);
    RUN_TEST(shouldWriteNoCommandFoundToResponseBuffer_whenNoCommandIsFound);
    RUN_TEST(shouldWriteValidationErrorMessageToBuffer_onExecuteWithInvalidNumberOfArguments);
    RUN_TEST(shouldWriteHelloToResponseBuffer_onInputExecution);
    return UNITY_END();
}
