#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include "command.h"
#include "commandMap.h"
#include "projectConstants.h"
#include "stringUtils.h"
#include <stdint.h>

#define INVALID_COMMAND_MESSAGE "Command '%s' not found\n\r"

void splitInputIntoCommandAndArgs(char * input, uint8_t inputLength, char * commandLabelBuffer, uint8_t * argc, char argv[MAX_ARGS][MAX_ARG_LENGTH]);

void executeInput(commandMap_t * commandMap, char * commandLabel, uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize);

#endif