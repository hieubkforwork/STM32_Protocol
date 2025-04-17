#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_

#include "stm32f1.h"
typedef struct  GPIO_PinDef
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPull;
    uint8_t GPIO_OutType;
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
uint8_t digitalWrite(GPIO_RegDef* pGPIOx, uint8_t pinNum, uint8_t Value);
uint8_t TogglePin(GPIO_RegDef* pGPIOx, uint8_t pinNum);

void GPIO_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void GPIO_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNum);




#endif