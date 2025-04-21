#include "stm32_gpio.h"

void GPIO_ClockControl(GPIO_RegDef *pGPIOx, uint8_t State)
{
    if (State == ENABLE)
    {
        if (pGPIOx == GPIOA)
            GPIOA_PCLK_EN();
        if (pGPIOx == GPIOB)
            GPIOB_PCLK_EN();
        if (pGPIOx == GPIOC)
            GPIOC_PCLK_EN();
        if (pGPIOx == GPIOD)
            GPIOD_PCLK_EN();
        if (pGPIOx == GPIOE)
            GPIOE_PCLK_EN();
        if (pGPIOx == GPIOF)
            GPIOF_PCLK_EN();
        if (pGPIOx == GPIOG)
            GPIOG_PCLK_EN();
    }
    else
    {
    }
}
void GPIO_Init(GPIO_Handle_T *pGPIO_Handle)
{
    // 1.Config Mode/Speed/Output Type

    uint32_t position = pGPIO_Handle->GPIO_PIN.GPIO_PinNumber;
    uint32_t temp = 0;
    uint32_t shift = (position % 8) * 4; // 1 thanh ghi 32 bits có 8 pin, mỗi pin 4 bits

    volatile uint32_t *config_reg;

    GPIO_ClockControl(pGPIO_Handle->pGPIOx, ENABLE);

    // Chọn thanh ghi CRL hoặc CRH
    if (position < 8)
    {
        config_reg = &pGPIO_Handle->pGPIOx->CRL;
    }
    else
    {
        config_reg = &pGPIO_Handle->pGPIOx->CRH;
    }

    // Xóa 4 bit cũ
    *config_reg &= ~(0xF << shift);

    // Khai báo các biến cho EXTI
    uint8_t pinNumber = position;
    uint8_t exti_index;
    uint8_t exti_pos;
    uint8_t port_code;

   
   

    switch (pGPIO_Handle->GPIO_PIN.GPIO_PinMode)
    {
    case GPIO_MODE_ANALOG:
        /* code */
        break;
    case GPIO_MODE_INPUT:
        // CNF = 10, MODE = 00
        *config_reg |= (0x8 << shift);
        if (pGPIO_Handle->GPIO_PIN.GPIO_PinPull == GPIO_PULLUP)
            pGPIO_Handle->pGPIOx->ODR |= (1 << position);
        else if (pGPIO_Handle->GPIO_PIN.GPIO_PinPull == GPIO_PULLDOWN)
            pGPIO_Handle->pGPIOx->ODR &= ~(1 << position);
        break;
    case GPIO_MODE_OUTPUT_PP:
        // CNF = 00, MODE = speed
        temp = (pGPIO_Handle->GPIO_PIN.GPIO_PinSpeed & 0x03); // chỉ lấy 2 bit
        *config_reg |= (temp << shift);
        break;
    case GPIO_MODE_OUTPUT_OD:
        // CNF = 01, MODE = speed
        temp = ((0x1 << 2) | (pGPIO_Handle->GPIO_PIN.GPIO_PinSpeed & 0x03)); // CNF = 01, MODE = speed
        *config_reg |= (temp << shift);
        break;
    case GPIO_MODE_AF_PP:
        // CNF = 10, MODE = speed
        temp = ((0x1 << 3) | (pGPIO_Handle->GPIO_PIN.GPIO_PinSpeed & 0x03));
        *config_reg |= (temp << shift);
        break;
    case GPIO_MODE_AF_OD:
        // CNF = 10, MODE = speed
        temp = ((0x03 << 2) | (pGPIO_Handle->GPIO_PIN.GPIO_PinSpeed & 0x03));
        *config_reg |= (temp << shift);
        break;
    case GPIO_MODE_IT_FS:
        AFIO_PCLK_EN();

        // CNF = 10, MODE = 00
        *config_reg |= (0x8 << shift); // CNF=10, MODE=00
        if (pGPIO_Handle->GPIO_PIN.GPIO_PinPull == GPIO_PULLUP)
            pGPIO_Handle->pGPIOx->ODR |= (1 << position);
        else if (pGPIO_Handle->GPIO_PIN.GPIO_PinPull == GPIO_PULLDOWN)
            pGPIO_Handle->pGPIOx->ODR &= ~(1 << position);

        // Cấu hình EXTI (ngắt)
        EXTI->RTSR &= ~(1 << pinNumber);
        EXTI->FTSR |= (1 << pinNumber); // Cạnh xuống
        EXTI->IMR |= (1 << pinNumber);

        exti_index = pinNumber / 4;
        exti_pos = (pinNumber % 4) * 4;
        port_code = GPIO_BASE_TO_CODE(pGPIO_Handle->pGPIOx);

        AFIO->EXTICR[exti_index] &= ~(0xF << exti_pos);
        AFIO->EXTICR[exti_index] |= (port_code << exti_pos);
        break;
    case GPIO_MODE_IT_RS:
        AFIO_PCLK_EN();

        // CNF = 10, MODE = 00
        *config_reg |= (0x8 << shift); // CNF=10, MODE=00
        if (pGPIO_Handle->GPIO_PIN.GPIO_PinPull == GPIO_PULLUP)
            pGPIO_Handle->pGPIOx->ODR |= (1 << position);
        else if (pGPIO_Handle->GPIO_PIN.GPIO_PinPull == GPIO_PULLDOWN)
            pGPIO_Handle->pGPIOx->ODR &= ~(1 << position);

        // Cấu hình EXTI (ngắt)
        EXTI->FTSR &= ~(1 << pinNumber);
        EXTI->RTSR |= (1 << pinNumber); // Cạnh lên
        EXTI->IMR |= (1 << pinNumber);

        exti_index = pinNumber / 4;
        exti_pos = (pinNumber % 4) * 4;
        port_code = GPIO_BASE_TO_CODE(pGPIO_Handle->pGPIOx);

        AFIO->EXTICR[exti_index] &= ~(0xF << exti_pos);
        AFIO->EXTICR[exti_index] |= (port_code << exti_pos);

        break;
    default:
        break;
    }
}

void GPIO_DeInit(GPIO_RegDef *pGPIOx)
{
    if (pGPIOx == GPIOA)
        GPIOA_REG_RESET();
    if (pGPIOx == GPIOB)
        GPIOB_REG_RESET();
    if (pGPIOx == GPIOC)
        GPIOC_REG_RESET();
    if (pGPIOx == GPIOD)
        GPIOD_REG_RESET();
    if (pGPIOx == GPIOE)
        GPIOE_REG_RESET();
    if (pGPIOx == GPIOF)
        GPIOF_REG_RESET();
    if (pGPIOx == GPIOG)
        GPIOG_REG_RESET();
}
uint8_t digitalRead(GPIO_RegDef *pGPIOx, uint8_t pinNum)
{
    return (pGPIOx->IDR >> pinNum) & 0x1;
}
void digitalWrite(GPIO_RegDef *pGPIOx, uint8_t pinNum, uint8_t Value)
{
    if (Value == HIGH)
    {
        pGPIOx->ODR |= (1 << pinNum);
    }
    else
    {
        pGPIOx->ODR &= ~(1 << pinNum);
    }
}
void TogglePin(GPIO_RegDef *pGPIOx, uint8_t pinNum)
{
    pGPIOx->ODR ^= (1 << pinNum);
}

void NVIC_IRQInterruptCfg(uint8_t IRQNum, uint8_t State)
{
    if (State == ENABLE)
    {
        if (IRQNum <= 31)
            *NVIC_ISER0 |= (1 << IRQNum);
        else if (IRQNum > 31 && IRQNum <= 63)
            *NVIC_ISER1 |= (1 << (IRQNum % 32));
        else if (IRQNum > 63 && IRQNum <= 95)
            *NVIC_ISER2 |= (1 << (IRQNum % 64));
    }
    else
    {
        if (IRQNum <= 31)
            *NVIC_ICER0 |= (1 << IRQNum);
        else if (IRQNum > 31 && IRQNum <= 63)
            *NVIC_ICER1 |= (1 << (IRQNum % 32));
        else if (IRQNum > 63 && IRQNum <= 95)
            *NVIC_ICER2 |= (1 << (IRQNum % 64));
    }
}
void NVIC_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority)
{
    uint8_t ipr = IRQNum / 4;
    uint8_t irq = IRQNum % 4;
    *(NVIC_PR_BASEADDR + ipr) &= ~(0xF << (8 * irq + 4)); // Clear 4 bits
    *(NVIC_PR_BASEADDR + ipr) |= (IRQPriority << (8 * irq + 4));
}
void NVIC_IRQHandling(uint8_t PinNum)
{
    if (EXTI->PR & (1 << PinNum))
    {
        EXTI->PR |= (1 << PinNum);
    }
}

void PinMode(GPIO_RegDef *pGPIOx, uint8_t PIN, uint8_t MODE)
{
    GPIO_Handle_T GPIO_Handle;
    GPIO_Handle.pGPIOx = pGPIOx;
    switch (MODE)
    {
    case INPUT:
        GPIO_Handle.GPIO_PIN.GPIO_PinNumber = PIN;
        GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_INPUT;
        GPIO_Handle.GPIO_PIN.GPIO_PinPull = GPIO_NOPULL;
        GPIO_Init(&GPIO_Handle);
        break;
    case INPUT_PULLUP:
        GPIO_Handle.GPIO_PIN.GPIO_PinNumber = PIN;
        GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_INPUT;
        GPIO_Handle.GPIO_PIN.GPIO_PinPull = GPIO_PULLUP;
        GPIO_Init(&GPIO_Handle);
        break;
    case INPUT_PULLDOWN:
        GPIO_Handle.GPIO_PIN.GPIO_PinNumber = PIN;
        GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_INPUT;
        GPIO_Handle.GPIO_PIN.GPIO_PinPull = GPIO_PULLDOWN;
        GPIO_Init(&GPIO_Handle);
        break;
    case OUTPUT:
        GPIO_Handle.GPIO_PIN.GPIO_PinNumber = PIN;
        GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
        GPIO_Handle.GPIO_PIN.GPIO_PinSpeed = GPIO_SPEED_2MHZ;
        GPIO_Init(&GPIO_Handle);
        break;
    case IT:
        GPIO_Handle.GPIO_PIN.GPIO_PinNumber = PIN;
        GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_IT_FS;
        GPIO_Handle.GPIO_PIN.GPIO_PinSpeed = GPIO_SPEED_2MHZ;
        GPIO_Handle.GPIO_PIN.GPIO_PinPull = GPIO_PULLUP;
        GPIO_Init(&GPIO_Handle);
        if (PIN == 0)
        {
            NVIC_IRQPriorityCfg(EXTI0_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI0_IRQn, ENABLE);
        }
        else if (PIN == 1)
        {
            NVIC_IRQPriorityCfg(EXTI1_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI1_IRQn, ENABLE);
        }
        else if (PIN == 2)
        {
            NVIC_IRQPriorityCfg(EXTI2_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI2_IRQn, ENABLE);
        }
        else if (PIN == 3)
        {
            NVIC_IRQPriorityCfg(EXTI3_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI3_IRQn, ENABLE);
        }
        else if (PIN == 4)
        {
            NVIC_IRQPriorityCfg(EXTI4_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI4_IRQn, ENABLE);
        }
        else if (PIN >= 5 && PIN <= 10)
        {
            NVIC_IRQPriorityCfg(EXTI9_5_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI9_5_IRQn, ENABLE);
        }
        else if (PIN >= 11 && PIN <= 15)
        {
            NVIC_IRQPriorityCfg(EXTI15_10_IRQn, 1);
            NVIC_IRQInterruptCfg(EXTI15_10_IRQn, ENABLE);
        }
        break;
    case ALT:
        GPIO_Handle.GPIO_PIN.GPIO_PinNumber = PIN;
        GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_AF_PP;
        GPIO_Handle.GPIO_PIN.GPIO_PinSpeed = GPIO_SPEED_50MHZ;
        GPIO_Handle.GPIO_PIN.GPIO_PinPull = GPIO_NOPULL;
        GPIO_Init(&GPIO_Handle);
    
    
        break;
    default:
        break;
    }
}
