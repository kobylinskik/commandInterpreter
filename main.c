#include <stdint.h>
#include <string.h>
#include "stm32f10x.h"
#include "setupClocks.c"
#include "command.h"
#include "commandMap.h"

void readUartData(char * buffer, uint8_t bufferSize, uint8_t * msgLength) {
    char dataFrame = 0;
    *msgLength = 0;
    do {
        if (USART2->SR & (1<<5)) {
            dataFrame = USART2->DR;
            buffer[(*msgLength)++] = dataFrame;
        }
    } while (dataFrame != '\r' && *msgLength < bufferSize);
    buffer[(*msgLength) -1] = 0;
}

char * testShit(uint8_t argc, char ** argv) {
    GPIOA->ODR |= 1<<5;
    return argv[0];
}

void test() {

}

int main(void) {
    setupClocks();
    setupPins();
    setupUsart2();

    char * test1 = "test2";
    char * test2 = "test1";
    int test3 = strcmp(test1, test2);

    char commandBuffer[30];
    uint8_t commandLength = 0;
    
    char * commandLabel = "test";
    command_t command;
    command.label = commandLabel;
    command.function = *testShit;

    commandMap_t cmap;
    initMap(&cmap);
    put(&cmap, &command);

    while (1) {
        readUartData(commandBuffer, 30, &commandLength);
        test();

        command_t * com = get(&cmap, commandBuffer);
        execute(com, 0, &commandBuffer);
    }
}