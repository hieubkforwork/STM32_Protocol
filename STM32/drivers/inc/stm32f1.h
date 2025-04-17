#ifndef INC_STM32F103XX_H_  // Nếu INC_STM32F103XX_H_ chưa được định nghĩa
#define INC_STM32F103XX_H_  // thì định nghĩa nó

#include<stdint.h>

#define enable 1
#define disable 0
#define SET enable
#define RESET disable
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET
#define FLAG_SET SET
#define FLAG_RESET RESET

//BASE ADDRESS
#define FLASH_BASEADDR       0x08000000U
#define SRAM_BASEADDR        0x20000000U 
#define ROM_BASEADDR         0x1FFFF000U
#define SRAM SRAM_BASEADDR

//BUS ADDRESS
#define PERIPH_BASEADDR      0x40000000U
#define APB1PERIPH_BASEADDR PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR  0x40010000U
#define AHBPERIPH_BASEADDR  0x40018000U

//GPIO
#define GPIOA_BASEADDR   (APB2PERIPH_BASEADDR + 0x00000800U)
#define GPIOB_BASEADDR   (APB2PERIPH_BASEADDR + 0x00000C00U)
#define GPIOC_BASEADDR   (APB2PERIPH_BASEADDR + 0x00001000U)
#define GPIOD_BASEADDR   (APB2PERIPH_BASEADDR + 0x00001400U)
#define GPIOE_BASEADDR   (APB2PERIPH_BASEADDR + 0x00001800U)
#define GPIOF_BASEADDR   (APB2PERIPH_BASEADDR + 0x00001C00U)
#define GPIOG_BASEADDR   (APB2PERIPH_BASEADDR + 0x00002000U)

//CLK
#define RCC_BASEADDR (AHBPERIPH_BASEADDR + 0x00009000U)

// I2C (APB1)
#define I2C1_BASEADDR     (APB1PERIPH_BASEADDR + 0x00005400U)
#define I2C2_BASEADDR     (APB1PERIPH_BASEADDR + 0x00005800U)

// USART (APB1 và APB2)
#define USART2_BASEADDR   (APB1PERIPH_BASEADDR + 0x00004400U)
#define USART3_BASEADDR   (APB1PERIPH_BASEADDR + 0x00004800U)
#define USART1_BASEADDR   (APB2PERIPH_BASEADDR + 0x00003800U)
#if defined(STM32F103xE) || defined(STM32F103xG)
  #define UART4_BASEADDR   0x40004C00U
  #define UART5_BASEADDR   0x40005000U
#endif

// SPI (APB1 và APB2)
#define SPI3_BASEADDR     (APB1PERIPH_BASEADDR + 0x00003C00U)
#define SPI2_BASEADDR     (APB1PERIPH_BASEADDR + 0x00003800U)
#define SPI1_BASEADDR     (APB2PERIPH_BASEADDR + 0x00003000U)

// NGẮT
#define EXTI_BASEADDR       (APB2PERIPH_BASEADDR + 0x0400U)
#define AFIO_BASEADDR       (APB2PERIPH_BASEADDR + 0x0000U)





#define __vo volatile 
/*Trình biên dịch thường tối ưu hóa mã nguồn 
để giảm bớt số lần truy cập vào một biến trong 
quá trình thực thi, giả sử giá trị của nó không 
thay đổi trong suốt chương trình. Tuy nhiên, 
trong các ứng dụng nhúng (như với các vi xử lý
 hoặc các hệ thống phần cứng), các giá trị của
  biến có thể thay đổi bởi các yếu tố bên ngoài như:

//Bộ đếm thời gian (Timer)

//Ngắt (Interrupts)

Các thanh ghi phần cứng, đặc biệt là các thanh ghi
 I/O (Input/Output) hoặc GPIO

Do đó, volatile giúp đảm bảo rằng giá trị của biến 
luôn được đọc trực tiếp từ bộ nhớ mỗi lần, không bị
lưu vào bộ đệm hoặc tối ưu hóa quá mức.*/


// MEMORY MAP
typedef struct GPIO_RegDef
{
     __vo uint32_t CRH;
     __vo uint32_t IDR;
     __vo uint32_t ODR;
     __vo uint32_t BSRR;
     __vo uint32_t BRR;
     __vo uint32_t LCKR;
     __vo uint32_t AFR[2];
}GPIO_RegDef;
#define GPIOA ((GPIO_RegDef*) GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef*) GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef*) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef*) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef*) GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef*) GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef*) GPIOG_BASEADDR)

typedef struct RCC_RegDef
{
    __vo uint32_t CR;               //add:0x000
    __vo uint32_t CFGR;             //add:0x004
    __vo uint32_t CIR;              //add:0x008
    __vo uint32_t APB2RSTR;         //add:0x00C   
    __vo uint32_t APB1RSTR;         //add:0x010  
    __vo uint32_t AHBENR;           //add:0x014  
    __vo uint32_t APB2ENR;          //add:0x018   
    __vo uint32_t APB1ENR;          //add:0x01C   
    __vo uint32_t BDCR;             //add:0x020   
    __vo uint32_t CSR;              //add:0x024
    __vo uint32_t AHBSTR;           //add:0x028
    __vo uint32_t CFGR2;            //add:0x02C
}RCC_RegDef;
#define RCC ((RCC_RegDef*) RCC_BASEADDR)

typedef struct EXTI_RegDef
{
    __vo uint32_t IMR;
    __vo uint32_t EMR;
    __vo uint32_t RTSR;
    __vo uint32_t FTSR;
    __vo uint32_t SWIER;
    __vo uint32_t PR;
}EXTI_RegDef;
#define EXTI ((EXTI_RegDef*) EXTI_BASEADDR)

typedef struct SPI_RegDef
{
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t SR;
    __vo uint32_t DR;
    __vo uint32_t CRCPR;
    __vo uint32_t RXCRCR;
    __vo uint32_t TXCRCR;
    __vo uint32_t I2SCFGR;
    __vo uint32_t I2SPR;
}SPI_RegDef;
#define SPI1 ((SPI_RegDef*) SPI1_BASEADDR )
#define SPI2 ((SPI_RegDef*) SPI2_BASEADDR )
#define SPI3 ((SPI_RegDef*) SPI3_BASEADDR )
typedef struct I2C_RegDef
{
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t OAR1;
    __vo uint32_t OAR2;
    __vo uint32_t DR;
    __vo uint32_t SR1;
    __vo uint32_t SR2;
    __vo uint32_t CCR;
    __vo uint32_t TRISE;
}I2C_RegDef;
#define I2C1 ((I2C_RegDef*) I2C1_BASEADDR)
#define I2C2 ((I2C_RegDef*) I2C2_BASEADDR)

typedef struct USART_RegDef
{
    __vo uint32_t SR;
    __vo uint32_t DR;
    __vo uint32_t BRR;
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t CR3;
    __vo uint32_t GTPR;
}USART_RegDef;
#define USART1 ((USART_RegDef*) USART1_BASEADDR)
#define USART2 ((USART_RegDef*) USART2_BASEADDR)
#define USART3 ((USART_RegDef*) USART3_BASEADDR)
#define UART4 ((USART_RegDef*) UART4_BASEADDR)
#define UART5 ((USART_RegDef*) UART5_BASEADDR)

//
//======================================
//

//Bật CLK cho GPIO
#define GPIOA_PCLK_EN() (RCC->APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN() (RCC->APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN() (RCC->APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN() (RCC->APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN() (RCC->APB2ENR |= (1 << 6))
#define GPIOF_PCLK_EN() (RCC->APB2ENR |= (1 << 7))
#define GPIOG_PCLK_EN() (RCC->APB2ENR |= (1 << 8))

//Bật CLK cho I2C
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1 << 22))

//Bật CLK cho SPI
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1 << 15))

//Bật CLK cho UART
#define USART1_PCLK_EN() (RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN() (RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN() (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN() (RCC->APB1ENR |= (1 << 20))

#define AFIO_PCLK_EN() (RCC->APB2ENR |= (1 << 0))

//
//======================================
//

//Tắt CLK cho GPIO
#define GPIOA_PCLK_DI() (RCC->APB2ENR &=~ (1 << 2))
#define GPIOB_PCLK_DI() (RCC->APB2ENR &=~ (1 << 3))
#define GPIOC_PCLK_DI() (RCC->APB2ENR &=~ (1 << 4))
#define GPIOD_PCLK_DI() (RCC->APB2ENR &=~ (1 << 5))
#define GPIOE_PCLK_DI() (RCC->APB2ENR &=~ (1 << 6))
#define GPIOF_PCLK_DI() (RCC->APB2ENR &=~ (1 << 7))
#define GPIOG_PCLK_DI() (RCC->APB2ENR &=~ (1 << 8))

//Tắt CLK cho I2C
#define I2C1_PCLK_DI() (RCC->APB1ENR &=~ (1 << 21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &=~ (1 << 22))

//Tắt CLK cho SPI
#define SPI1_PCLK_DI() (RCC->APB2ENR &=~ (1 << 12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &=~ (1 << 14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &=~ (1 << 15))

//Tắt CLK cho UART
#define USART1_PCLK_DI() (RCC->APB2ENR &=~ (1 << 14))
#define USART2_PCLK_DI() (RCC->APB1ENR &=~ (1 << 17))
#define USART3_PCLK_DI() (RCC->APB1ENR &=~ (1 << 18))
#define UART4_PCLK_DI() (RCC->APB1ENR &=~ (1 << 19))
#define UART5_PCLK_DI() (RCC->APB1ENR &=~ (1 << 20))

#define AFIO_PCLK_DI() (RCC->APB2ENR &=~ (1 << 0))












#endif                      // Kết thúc bảo vệ



/*
STUDY NOTE:
STEP 1: Define memory address of specific registers
(FLASH, ROM, SRAM, Regions: APB1, APB2, AHPB, PORT GPIO, I2C, UART, SPI, EXTI, AFIO)
STEP 2: Mapping memory by using struct
STEP 3: Config CLK for specific register (enable, disable)


*/