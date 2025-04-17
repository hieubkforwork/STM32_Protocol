#include"stm32_gpio.h"

void GPIO_ClockControl( GPIO_RegDef*pGPIOx,uint8_t State){
    if(State == enable){
       if(pGPIOx == GPIOA) GPIOA_PCLK_EN();
       if(pGPIOx == GPIOB) GPIOB_PCLK_EN(); 
       if(pGPIOx == GPIOC) GPIOC_PCLK_EN();      
       if(pGPIOx == GPIOD) GPIOD_PCLK_EN(); 
       if(pGPIOx == GPIOE) GPIOE_PCLK_EN(); 
       if(pGPIOx == GPIOF) GPIOF_PCLK_EN(); 
       if(pGPIOx == GPIOG) GPIOG_PCLK_EN(); 
    }
    else{
        
    }
}
void GPIO_Init(GPIO_Handle_T* pGPIO_Handle);
void GPIO_DeInit(GPIO_RegDef* pGPIOx);
uint8_t digitalRead(GPIO_RegDef* pGPIOx, uint8_t pinNum);
uint8_t digitalWrite(GPIO_RegDef* pGPIOx, uint8_t pinNum, uint8_t Value);
uint8_t TogglePin(GPIO_RegDef* pGPIOx, uint8_t pinNum);

void GPIO_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void GPIO_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNum);