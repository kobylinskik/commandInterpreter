#include "stringUtils.h"

uint8_t stringsMatch(char * str1, char * str2, uint8_t maxSize) {
    for (uint8_t i; i < maxSize && (str1[i] != '\0' || str2[i] != '\0'); i++) {
        if (str1[i] != str2[i]) {
            return 0;
        }
    }
    return 1;
};

void tes() {

};

void writeMessageToBuffer(char * message, char ** argv, char * buffer, uint8_t bufferSize) {
    uint8_t argNumber = 0;
    while (*message && bufferSize) {
        if (*message == '%' && *(message + 1) == 's') {
            message += 2;
            char * argVal = (char *)*argv;
            while (*argVal) {
                tes();
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