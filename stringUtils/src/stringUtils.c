#include "stringUtils.h"

uint8_t stringsMatch(char * str1, char * str2, uint8_t maxSize) {
    for (uint8_t i = 0; i < maxSize && (str1[i] != '\0' || str2[i] != '\0'); i++) {
        if (str1[i] != str2[i]) {
            return 0;
        }
    }
    return 1;
};

void strCopy(char originString[20], char targetString[20], uint8_t maxSize) {
    while (originString && maxSize--) {
        *(targetString++) = *originString++;
    }
}

void writeMessageToBuffer(char * message, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * buffer, uint8_t bufferSize) {
    uint8_t argNumber = 0;
    while (*message && bufferSize) {
        if (*message == '%' && *(message + 1) == 's') {
            message += 2;
            char * argVal = (char *)*argv;
            while (*argVal) {
                *(buffer++) = *(argVal++);
                bufferSize--;
            }
            argNumber++;
            argv++;
        } else {
            *(buffer++) = *message++;
            bufferSize--;
        }
        *buffer = 0;
    }
}