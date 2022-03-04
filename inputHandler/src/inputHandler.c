#include "inputHandler.h"

void splitInputIntoCommandAndArgs(char * input, uint8_t inputLength, char * commandLabelBuffer, uint8_t * argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]) {
    *argc = 0;
    while (*input != '(') {
        (*commandLabelBuffer++) = *input++;
    }
    *commandLabelBuffer = 0;
    input++;
    while (*input != 0) {
        char * processedArgument = *argv;
        while (*input != ',' && *input != ')') {
            *(processedArgument++) = *input++;
        }
        *processedArgument = 0;
        argv++;
        (*argc)++;
        input++;
    }
};

void executeInput(commandMap_t * commandMap, char * commandLabel, uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize) {
    command_t * command = get(commandMap, commandLabel);
    if (!command) {
        char messageArgv[MAX_ARGS][MAX_ARG_LENGTH];
        uint8_t i;
        for (i = 0; commandLabel[i]; i++) {
            messageArgv[0][i] = commandLabel[i];
        }
        messageArgv[0][i] = 0;
        writeMessageToBuffer(INVALID_COMMAND_MESSAGE, messageArgv, responseBuffer, responseBufferSize);
        return;
    }
    if (validateParams(command, argc, argv, responseBuffer, responseBufferSize)) {
        return;
    }
    execute(command, argc, argv, responseBuffer, responseBufferSize);
};