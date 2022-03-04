#include "validationUtils.h"
#include "stdio.h"

uint8_t validateArgc(uint8_t argc, uint8_t expectedArgc, char * responseBuffer, uint8_t responseBufferSize) {
    if (argc != expectedArgc) {
        char argv[MAX_ARGS][MAX_ARG_LENGTH];
        argv[0][0] = '0' + expectedArgc;
        argv[0][1] = 0;
        argv[1][0] = '0' + argc;
        argv[1][1] = 0;

        writeMessageToBuffer(INVALID_ARGC_MESSAGE, argv, responseBuffer, responseBufferSize);
        return 1;
    }
    return 0;
}