#ifndef __VALIDATION_UTILS__
#define __VALIDATION_UTILS__

#include "stringUtils.h"
#include <stdint.h>

#define INVALID_ARGC_MESSAGE "Invalid number of arguments. Expected %s, received %s arguments."

uint8_t validateArgc(uint8_t argc, uint8_t expectedArgc, char * responseBuffer, uint8_t responseBufferSize);

#endif