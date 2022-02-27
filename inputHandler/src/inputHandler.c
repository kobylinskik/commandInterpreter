#include <stdint.h>
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