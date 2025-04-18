#include"stm32_gpio.h"

void GPIO_ClockControl( GPIO_RegDef*pGPIOx,uint8_t State){
    if(State == ENABLE){
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
void GPIO_Init(GPIO_Handle_T* pGPIO_Handle){
    //1.Config Mode/Speed/Output Type

        uint32_t position = pGPIO_Handle->GPIO_PIN.GPIO_PinNumber;
        uint32_t temp = 0;
        uint32_t shift = (position % 8) * 4;
    
        volatile uint32_t *config_reg;

        GPIO_ClockControl(pGPIO_Handle->pGPIOx, ENABLE);

        // Chọn thanh ghi CRL hoặc CRH
        if (position < 8) {
            config_reg = &pGPIO_Handle->pGPIOx->CRL;
        } else {
            config_reg = &pGPIO_Handle->pGPIOx->CRH;
        }
    
        // Xóa 4 bit cũ
        *config_reg &= ~(0xF << shift);
    
        // Cấu hình bit mới
        if (pGPIO_Handle->GPIO_PIN.GPIO_PinMode <= 0x03) {
            // Input mode
            temp = (pGPIO_Handle->GPIO_PIN.GPIO_PinMode << 2);
        } 
        else if(pGPIO_Handle->GPIO_PIN.GPIO_PinMode > 0x03 && pGPIO_Handle->GPIO_PIN.GPIO_PinMode <= 0x08){
            // Output mode
            temp = ((pGPIO_Handle->GPIO_PIN.GPIO_PinMode - 0x04) << 2) | 
                   (pGPIO_Handle->GPIO_PIN.GPIO_PinSpeed);
        }
        else {
            // Interrupt mode
            if(pGPIO_Handle->GPIO_PIN.GPIO_PinMode == GPIO_MODE_IT_FS){
                   EXTI->FTSR |= ( 1 << pGPIO_Handle->GPIO_PIN.GPIO_PinMode);
                   EXTI->RTSR &=~( 1 << pGPIO_Handle->GPIO_PIN.GPIO_PinMode);
            }
            else if (pGPIO_Handle->GPIO_PIN.GPIO_PinMode == GPIO_MODE_IT_RS){
                   EXTI->FTSR &=~ ( 1 << pGPIO_Handle->GPIO_PIN.GPIO_PinMode);
                   EXTI->RTSR |=  ( 1 << pGPIO_Handle->GPIO_PIN.GPIO_PinMode);
            }
        }
    
        // Ghi vào thanh ghi
        *config_reg |= (temp << shift);
    
    //2.Config Pull Up/Down
    if(pGPIO_Handle-> GPIO_PIN.GPIO_PinPull == GPIO_PULLUP){
        pGPIO_Handle->pGPIOx->ODR |= (1 << position); 
    }
    else pGPIO_Handle->pGPIOx->ODR &= ~(1 << position);
    
}
void GPIO_DeInit(GPIO_RegDef* pGPIOx){
    if(pGPIOx == GPIOA) GPIOA_REG_RESET();
    if(pGPIOx == GPIOB) GPIOB_REG_RESET(); 
    if(pGPIOx == GPIOC) GPIOC_REG_RESET();      
    if(pGPIOx == GPIOD) GPIOD_REG_RESET(); 
    if(pGPIOx == GPIOE) GPIOE_REG_RESET(); 
    if(pGPIOx == GPIOF) GPIOF_REG_RESET(); 
    if(pGPIOx == GPIOG) GPIOG_REG_RESET(); 
}
uint8_t digitalRead(GPIO_RegDef* pGPIOx, uint8_t pinNum){
    uint8_t value;
   return value = (uint8_t)(pGPIOx->IDR >> pinNum)& 0x00000001;
}
void digitalWrite(GPIO_RegDef* pGPIOx, uint8_t pinNum, uint8_t Value){
    if(Value == HIGH){
        pGPIOx->ODR |= (1 << pinNum);
    }
    else {
        pGPIOx->ODR &= ~(1 << pinNum);
    }
}
uint8_t TogglePin(GPIO_RegDef* pGPIOx, uint8_t pinNum);

void GPIO_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void GPIO_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNum);