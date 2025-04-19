#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_

#include "stm32f1.h"

//PIN
#define GPIO_PIN_0                  0
#define GPIO_PIN_1                  1
#define GPIO_PIN_2                  2
#define GPIO_PIN_3                  3
#define GPIO_PIN_4                  4
#define GPIO_PIN_5                  5
#define GPIO_PIN_6                  6
#define GPIO_PIN_7                  7
#define GPIO_PIN_8                  8
#define GPIO_PIN_9                  9
#define GPIO_PIN_10                 10
#define GPIO_PIN_11                 11
#define GPIO_PIN_12                 12
#define GPIO_PIN_13                 13
#define GPIO_PIN_14                 14
#define GPIO_PIN_15                 15
//MODE

#define INPUT                       0
#define INPUT_PULLUP                1    
#define INPUT_PULLDOWN              2
#define OUTPUT                      3
#define IT                          4

#define GPIO_MODE_ANALOG             0
#define GPIO_MODE_INFLOAT            1
#define GPIO_MODE_INPUT              2

#define GPIO_MODE_OUTPUT_PP          3
#define GPIO_MODE_OUTPUT_OD          4
#define GPIO_MODE_AF_PP              5
#define GPIO_MODE_AF_OD              6
//IT
#define GPIO_MODE_IT_FS              7
#define GPIO_MODE_IT_RS              8

//SPEED
#define GPIO_SPEED_10MHZ             1
#define GPIO_SPEED_2MHZ              2
#define GPIO_SPEED_50MHZ             3
//PULL
#define GPIO_NOPULL                     2
#define GPIO_PULLUP                     1
#define GPIO_PULLDOWN                   0

typedef struct  GPIO_PinDef
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPull;
    uint8_t GPIO_ALT;

} GPIO_PinDef;

typedef struct GPIO_Handle_T
{
    GPIO_RegDef*pGPIOx;
    GPIO_PinDef GPIO_PIN;
} GPIO_Handle_T;

void GPIO_ClockControl( GPIO_RegDef*pGPIOx,uint8_t State);
void GPIO_Init(GPIO_Handle_T* pGPIO_Handle);
void GPIO_DeInit(GPIO_RegDef* pGPIOx);
uint8_t digitalRead(GPIO_RegDef* pGPIOx, uint8_t pinNum);
void digitalWrite(GPIO_RegDef* pGPIOx, uint8_t pinNum, uint8_t Value);
void TogglePin(GPIO_RegDef* pGPIOx, uint8_t pinNum);

void NVIC_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void NVIC_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void NVIC_IRQHandling(uint8_t PinNum);
void PinMode(GPIO_RegDef*pGPIOx, uint8_t PIN, uint8_t MODE);



#endif