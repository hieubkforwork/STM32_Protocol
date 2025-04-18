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
#define GPIO_MODE_ANALOG             0x00
#define GPIO_MODE_INFLOAT            0x01
#define GPIO_MODE_INPUT              0x02

#define GPIO_MODE_OUTPUT_PP          0x04
#define GPIO_MODE_OUTPUT_OD          0x05
#define GPIO_MODE_AF_PP              0x06
#define GPIO_MODE_AF_OD              0x07
//IT
#define GPIO_MODE_IT_FS              0x09
#define GPIO_MODE_IT_RS              0x10

//SPEED
#define GPIO_SPEED_10MHZ             0x01
#define GPIO_SPEED_2MHZ              0x02
#define GPIO_SPEED_50MHZ             0x03
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
uint8_t TogglePin(GPIO_RegDef* pGPIOx, uint8_t pinNum);

void GPIO_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void GPIO_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNum);




#endif