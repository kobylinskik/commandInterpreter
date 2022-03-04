#include "commandData.h"
#include "inputHandler.h"
#include "projectConstants.h"
#include "setupClocks.c"
#include "stm32f10x.h"
#include <stdint.h>

void readUartData(char * buffer, uint8_t bufferSize, uint8_t * msgLength) {
    char dataFrame = 0;
    *msgLength = 0;
    do {
        if (USART2->SR & (1 << 5)) {
            dataFrame = USART2->DR;
            buffer[(*msgLength)++] = dataFrame;
            while (!(USART2->SR & (1 << 7))) {
            }
            USART2->DR = dataFrame;
        }
    } while (dataFrame != '\r' && *msgLength < bufferSize);
    while (!(USART2->SR & (1 << 7))) {
    }
    USART2->DR = '\n';
    buffer[(*msgLength) - 1] = 0;
}

void sendUartData(char message[RESPONSE_BUFFER_SIZE]) {
    while (*message) {
        while (!(USART2->SR & (1 << 7))) {
        }
        USART2->DR = *message++;
    }
}

void test() {}

int main(void) {
    setupClocks();
    setupUartPins();
    setupUsart2();

    commandMap_t cmap;
    initMap(&cmap);

    char * configurePinLabel = "configurePin";
    command_t configurePin;
    configurePin.label = configurePinLabel;
    configurePin.function = *configurePinFunction;
    configurePin.validation = *validateYoloPass;

    char * writePinLabel = "writePin";
    command_t writePin;
    writePin.label = writePinLabel;
    writePin.function = *writePinFunction;
    writePin.validation = *validateYoloPass;

    put(&cmap, &configurePin);
    put(&cmap, &writePin);

    char commandBuffer[100];
    uint8_t commandLength = 0;

    char commandLabelBuffer[30];
    uint8_t argc;

    char argv[MAX_ARGS][MAX_ARG_LENGTH];

    char responseBuffer[RESPONSE_BUFFER_SIZE];

    while (1) {
        readUartData(commandBuffer, 100, &commandLength);

        splitInputIntoCommandAndArgs(commandBuffer, 100, commandLabelBuffer, &argc, argv);
        executeInput(&cmap, commandLabelBuffer, argc, argv, responseBuffer, RESPONSE_BUFFER_SIZE);
        sendUartData(responseBuffer);
    }
}