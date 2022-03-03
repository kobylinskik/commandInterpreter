#include "inputHandler.h"

void splitInputIntoCommandAndArgs(char * input, uint8_t inputLength, char * commandLabelBuffer, uint8_t * argc, char ** argv) {
    *argc = 0;
    while (*input != '(') {
        (*commandLabelBuffer++) = *input++;
    }
    input++;
    while (*input != 0) {
        char * processedArgument = argv[*argc];
        while (*input != ',' && *input != ')') {
            *(processedArgument++) = *input++;
        }
        (*argc)++;
        input++;
    }
};

void executeInput(commandMap_t * commandMap, char * commandLabel, uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize) {
    command_t * command = get(commandMap, commandLabel);
    if (!command) {
        writeMessageToBuffer(INVALID_COMMAND_MESSAGE, &commandLabel, responseBuffer, responseBufferSize);
        return;
    }
    if (validateParams(command, argc, argv, responseBuffer, responseBufferSize)) {
        return;
    }
};