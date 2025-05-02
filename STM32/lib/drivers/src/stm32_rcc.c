#include"stm32_rcc.h"

uint32_t RCC_GetPCLK1Value(void){
    uint32_t pclk1,sysclk;
    uint8_t clksrc, temp,ahbp_scale, apb1_scale;
    uint16_t AHB_PreScaler[8]= {2,4,8,16,64,128,256,512};
    uint8_t APB1_PreScaler[4]= {2,4,8,16};
    //SYSCLK
    clksrc = (RCC->CFGR >> 2) & 0x03;
    if(clksrc == 0){
        sysclk = 8000000; //HSI
    }
    else if(clksrc == 1){
        sysclk = 8000000; //HSE: Used external Crystal 4-16 MHz
    }
    else if(clksrc == 2){ //PLL
        }
    //AHBCLK
    temp = (RCC->CFGR >> 4) & 0xF;
    if(temp < 8){
        ahbp_scale = 1;
    }
    else ahbp_scale = AHB_PreScaler[temp-8];
    //APB1CLK
    temp = (RCC->CFGR >> 8) & 0x7;
    if(temp < 4){
        apb1_scale = 1;
    }
    else apb1_scale = APB1_PreScaler[temp-4];

    pclk1 = (sysclk/ahbp_scale)/apb1_scale;
    return pclk1;
}
uint32_t RCC_GetPCLK2Value(void){
    uint32_t pclk2,sysclk;
    uint8_t clksrc, temp,ahbp_scale, apb2_scale;
    uint16_t AHB_PreScaler[8]= {2,4,8,16,64,128,256,512};
    uint8_t APB2_PreScaler[4]= {2,4,8,16};
    //SYSCLK
    clksrc = (RCC->CFGR >> 2) & 0x03;
    if(clksrc == 0){
        sysclk = 8000000; //HSI
    }
    else if(clksrc == 1){
        sysclk = 8000000; //HSE: Used external Crystal 4-16 MHz
    }
    else if(clksrc == 2){ //PLL
        }
    //AHBCLK
    temp = (RCC->CFGR >> 4) & 0xF;
    if(temp < 8){
        ahbp_scale = 1;
    }
    else ahbp_scale = AHB_PreScaler[temp-8];
    //APB1CLK
    temp = (RCC->CFGR >> 11) & 0x7;
    if(temp < 4){
        apb2_scale = 1;
    }
    else apb2_scale = APB2_PreScaler[temp-4];

    pclk2 = (sysclk/ahbp_scale)/apb2_scale;
    return pclk2;
}