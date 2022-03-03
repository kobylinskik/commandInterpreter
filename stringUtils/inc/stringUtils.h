#ifndef __STRING_UTILS__
#define __STRING_UTILS__

#include <stdint.h>

uint8_t stringsMatch(char * str1, char * str2, uint8_t maxSize);
void writeMessageToBuffer(char * message, char ** argv, char * buffer, uint8_t bufferSize);

#endif