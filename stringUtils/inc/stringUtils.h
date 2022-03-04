#ifndef __STRING_UTILS__
#define __STRING_UTILS__

#include "projectConstants.h"
#include <stdint.h>

uint8_t stringsMatch(char * str1, char * str2, uint8_t maxSize);
void writeMessageToBuffer(char * message, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * buffer, uint8_t bufferSize);

#endif