#include <stdint.h>
#include "stm32f10x.h"

#define USART_BAUD_RATE 0xEA6

void setupClocks() {
    //Enable USART2
    RCC->APB1ENR |= 1<<17;
    //Enable GPIOA
    RCC->APB2ENR |= 1<<2;
    //Configure system clock to PLL, PLL source -> HSI/2, multiplied x9 ((8MHz/2) * 9 = 36 MHz). 
    //HSI is the default PLL source
    RCC->CFGR |= ((1<<1) + (1<<18) + (1<<19));
    RCC->CR |= (1 + (1<<24));
}

void setupPins() {
    //PA2 -> TX -> AF PP
    //PA3 -> RX -> Floating in / input w pull-up
    //PA5 -> dioda -> GP PP
    //PA2:
    GPIOA->CRL |= (1 + (1<<2) + (1<<3))<<8;
    //PA3: default    
    //PA5:
    GPIOA->CRL |= 1<<20;
    GPIOA->CRL &= ~(1<<22);
}

void setupUsart2() {
    USART2->BRR = USART_BAUD_RATE;
    USART2->GTPR = (1<<2);
    USART2->CR1 |= ((1<<2) + (1<<3) + (1<<13));
}