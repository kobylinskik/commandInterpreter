#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include "command.h"
#include "commandMap.h"
#include "stringUtils.h"
#include <stdint.h>

#define INVALID_COMMAND_MESSAGE "Command '%s' not found\n"

void splitInputIntoCommandAndArgs(char * input, uint8_t inputLength, char * commandLabelBuffer, uint8_t * argc, char ** argv);

void executeInput(commandMap_t * commandMap, char * commandLabel, uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize);

#endif