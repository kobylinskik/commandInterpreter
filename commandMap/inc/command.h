#ifndef __COMMAND__

#define __COMMAND__

#include "stringUtils.h"
#include <stdint.h>

typedef struct {
    uint8_t (*function)(uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize);
    uint8_t (*validation)(uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize);
    char * label;
} command_t;

uint8_t validateParams(command_t * command, uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize);

uint8_t execute(command_t * command, uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize);

#endif