#include "commandData.h"
#include "stm32f10x.h"
#include "stringUtils.h"

GPIO_TypeDef * getGpioBankAddress(char bankSymbol) {
    switch (bankSymbol) {
    case 'a':
        return GPIOA;
    case 'A':
        return GPIOA;
    case 'b':
        return GPIOB;
    case 'B':
        return GPIOB;
    case 'c':
        return GPIOC;
    case 'C':
        return GPIOC;
    case 'd':
        return GPIOD;
    case 'D':
        return GPIOD;
    }
    return 0;
}

uint8_t configurePinValidation(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize) {
    if (argc != 4) {
        writeMessageToBuffer("Invalid number of arguments", argv, responseBuffer, responseBufferSize);
        return 1;
    }
}

uint8_t configurePinFunction(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize) {
    GPIO_TypeDef * gpio = getGpioBankAddress(argv[0][0]);
    volatile uint32_t * gpioCr;
    uint8_t pinNumber = argv[1][0] - '0';
    uint8_t pinOffset = pinNumber * 4;
    if (pinNumber < 8) {
        gpioCr = &(gpio->CRL);
    } else {
        gpioCr = &(gpio->CRH);
    }
    uint32_t orData = 0;
    uint32_t nandData = 0;
    if (stringsMatch("input", argv[2], MAX_ARG_LENGTH)) {
        nandData |= 3;
    } else if (stringsMatch("output10MHz", argv[2], MAX_ARG_LENGTH)) {
        orData |= 1;
        nandData |= 2;
    } else if (stringsMatch("output20MHz", argv[2], MAX_ARG_LENGTH)) {
        orData |= 2;
        nandData |= 1;
    } else if (stringsMatch("output50MHz", argv[2], 15)) {
        orData |= 3;
    }
    if (stringsMatch("analog", argv[3], 10) || stringsMatch("GP push-pull", argv[3], MAX_ARG_LENGTH)) {
        nandData |= 12;
    } else if (stringsMatch("floating", argv[3], 10) || stringsMatch("GP open-drain", argv[3], MAX_ARG_LENGTH)) {
        orData |= 4;
        nandData |= 8;
    } else if (stringsMatch("input w/pull-up", argv[3], 10) || stringsMatch("AF push-pull", argv[3], MAX_ARG_LENGTH)) {
        orData |= 8;
        nandData |= 4;
    } else if (stringsMatch("AF open-drain", argv[3], 10)) {
        orData |= 12;
    }
    *gpioCr |= (orData << pinOffset);
    *gpioCr &= ~(nandData << pinOffset);
    writeMessageToBuffer("Pin configured successfully\n\r", argv, responseBuffer, responseBufferSize);
}

uint8_t writePinFunction(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize) {
    GPIO_TypeDef * gpio = getGpioBankAddress(argv[0][0]);
    volatile uint32_t * gpioOdr = &(gpio->ODR);
    uint8_t pinNumber = argv[1][0] - '0';
    uint8_t pinValue = argv[2][0] - '0';
    if (pinValue) {
        *gpioOdr |= 1 << pinNumber;
    } else {
        *gpioOdr &= ~(1 << pinNumber);
    }
    writeMessageToBuffer("Pin value set successfully\n\r", argv, responseBuffer, responseBufferSize);
}

uint8_t validateYoloPass(uint8_t argc, char argv[MAX_ARGS][MAX_ARG_LENGTH], char * responseBuffer, uint8_t responseBufferSize) { return 0; }