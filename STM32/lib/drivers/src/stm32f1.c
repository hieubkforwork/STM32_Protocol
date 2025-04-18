#include"stm32f1.h"

void delay_ms(uint32_t ms) {
    for(uint32_t i = 0; i < ms; i++) {
        for(volatile uint32_t j = 0; j < 650; j++) {
            __asm("nop");
        }
    }
}

void delay_s(uint32_t s) {
    while(s--) {
        delay_ms(1000);
    }
}