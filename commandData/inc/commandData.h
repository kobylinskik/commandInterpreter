#ifndef __COMMAND_DATA__
#define __COMMAND_DATA__

#include "commandMap.h"
#include "projectConstants.h"
#include <stdint.h>

uint8_t configurePinFunction(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize);
uint8_t validateYoloPass(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize);
uint8_t writePinFunction(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize);

#endif