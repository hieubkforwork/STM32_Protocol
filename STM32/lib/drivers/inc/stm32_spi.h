#ifndef INC_STM32_SPI_H_
#define INC_STM32_SPI_H_

#include "stm32_spi.h"
#include "stm32f1.h"

#define MASTER 1
#define SLAVE  0
#define FULL_DUPLEX 1
#define HALF_DUPLEX 2
#define SIMPLE      3

#define SPEED_DIV2    0x0
#define SPEED_DIV4    0x1
#define SPEED_DIV8    0x2
#define SPEED_DIV16   0x3
#define SPEED_DIV32   0x4
#define SPEED_DIV64    0x5
#define SPEED_DIV128   0x6
#define SPEED_DIV256   0x7

#define DFF_8BITS       0x0
#define DFF_16BITS      0x1

#define CPOL_HIGH       1
#define CPOL_LOW        0

#define CPHA_HIGH       1
#define CPHA_LOW        0

#define SSM_EN          1
#define SSM_DI          0

typedef struct SPI_PinDef
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_ClkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
}SPI_PinDef;

typedef struct SPI_Handle_T
{
    SPI_RegDef*SPIx;
    SPI_PinDef SPI;
}SPI_Handle_T;

void SPI_ClockControl(SPI_RegDef*pSPIx,uint8_t STATE);
void SPI_PeripheralControl(SPI_RegDef *pSPIx, uint8_t STATE);
void SPI_Init(SPI_Handle_T*pSPI_Handle);
void SPI_DeInit(SPI_RegDef*pSPIx);  

void SPI_SSOEConfig(SPI_RegDef*pSPIx,uint8_t STATE);
void SPI_SendData(SPI_RegDef*pSPIx,uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef*pSPIx,uint8_t *pRxBuffer, uint32_t Len);

void SPI_SendDataIT(SPI_Handle_T*pSPI_Handle,uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveDataIT(SPI_Handle_T*pSPI_Handle,uint8_t *pRxBuffer, uint32_t Len);

void SPI_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void SPI_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_T*pSPI_Handle);


#endif