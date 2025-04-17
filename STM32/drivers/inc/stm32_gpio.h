#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_

#include "stm32f1.h"

#define GPIO_INPUT          0
#define GPIO_OUTPUT         1
#define GPIO_ALTE           2
#define GPIO_ANALOG         3
#define GPIO_MODE_IT_FL     4
#define GPIO_MODE_IT_RS     5
#define GPIO_MODE_IT_RFT    6
//TYPE
#define GPIO_TYPE_PP        0
#define GPIO_TYPE_OD        1
//SPEED
#define GPIO_SPEED_L        0
#define GPIO_SPEED_M        1
#define GPIO_SPEED_H        2
#define GPIO_SPEED_VH       3
//PULL
#define NO_PULL             0
#define PULL_UP             1
#define PULL_DOWN             2
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