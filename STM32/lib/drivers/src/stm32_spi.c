#include"stm32_spi.h"


void SPI_ClockControl(SPI_RegDef*pSPIx,uint8_t STATE){
    if(STATE == ENABLE){
        if(pSPIx == SPI1) SPI1_PCLK_EN();
        else if(pSPIx == SPI2) SPI2_PCLK_EN();
        else if(pSPIx == SPI3) SPI3_PCLK_EN();
    }
}
void SPI_Init(SPI_Handle_T *pSPI_Handle) {
    SPI_ClockControl(pSPI_Handle->SPIx, ENABLE);

    uint32_t temp = 0;

    temp |= pSPI_Handle->SPI.SPI_CPHA << 0;
    temp |= pSPI_Handle->SPI.SPI_CPOL << 1;
    temp |= pSPI_Handle->SPI.SPI_DeviceMode << 2;    // MSTR
    temp |= pSPI_Handle->SPI.SPI_ClkSpeed << 3;      // BR
    temp |= pSPI_Handle->SPI.SPI_SSM << 9;           // SSM
    temp |= pSPI_Handle->SPI.SPI_DFF << 11;          // DFF

    // Bus config
    if (pSPI_Handle->SPI.SPI_BusConfig == FULL_DUPLEX)
        temp &= ~(1 << 15); // BIDIMODE = 0
    else if (pSPI_Handle->SPI.SPI_BusConfig == HALF_DUPLEX)
        temp |= (1 << 15);  // BIDIMODE = 1
    else if (pSPI_Handle->SPI.SPI_BusConfig == SIMPLE) {
        temp &= ~(1 << 15); // BIDIMODE = 0
        temp |= (1 << 10);  // RXONLY = 1
    }

    // Gán CR1 trước
    pSPI_Handle->SPIx->CR1 = temp;

    // Nếu dùng phần mềm NSS (SSM = 1), thì set SSI = 1
    if (pSPI_Handle->SPI.SPI_SSM) {
        pSPI_Handle->SPIx->CR1 |= (1 << 8);  // SSI = 1
    }
}
void SPI_DeInit(SPI_RegDef*pSPIx);  

void SPI_SendData(SPI_RegDef *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    
        uint32_t i = 0;
    
        if (pSPIx->CR1 & (1 << 11)) // Check if DFF = 1 (16-bit data frame format)
        {
            uint16_t *data16 = (uint16_t *)pTxBuffer; // Cast to 16-bit pointer
    
            for (i = 0; i < Len / 2; i++)
            {
                // Wait until TXE (Transmit buffer empty)
                while (!(pSPIx->SR & (1 << 1)));
    
                pSPIx->DR = data16[i];
    
                // Wait until BSY (Busy flag) is reset
                while (pSPIx->SR & (1 << 7));
            }
    
            if (Len % 2) // Nếu còn dư 1 byte
            {
                // Wait until TXE
                while (!(pSPIx->SR & (1 << 1)));
    
                pSPIx->DR = ((uint16_t)pTxBuffer[Len - 1]) & 0x00FF; // Gửi 1 byte còn lại
    
                // Wait until BSY
                while (pSPIx->SR & (1 << 7));
            }
        }
        else // 8-bit data frame format
        {
            for (i = 0; i < Len; i++)
            {
                // Wait until TXE (Transmit buffer empty)
                while (!(pSPIx->SR & (1 << 1)));
    
                pSPIx->DR = pTxBuffer[i];
    
                // Wait until BSY (Busy flag) is reset
                while (pSPIx->SR & (1 << 7));
            }
        }
    
    
}


void SPI_ReceiveData(SPI_RegDef*pSPIx,uint8_t *pRxBuffer, uint32_t Len){
    if (pSPIx->CR1 & (1 << 11)) // DFF = 1 (16-bit mode)
    {
        uint16_t *pRxBuf16 = (uint16_t *)pRxBuffer;

        while (Len > 0)
        {
            while (!(pSPIx->SR & (1 << 1)));  // Wait until TXE = 1
            pSPIx->DR = 0xFFFF;               // Gửi dummy để tạo clock

            while (!(pSPIx->SR & (1 << 0))); // Wait until RXNE is set

            *pRxBuf16 = pSPIx->DR;
            pRxBuf16++;     // nhảy 2 byte
            Len -= 2;
        }
    }
    else // DFF = 0 (8-bit mode)
    {
        while (Len > 0)
        {
            while (!(pSPIx->SR & (1 << 1)));  // Wait until TXE = 1
            pSPIx->DR = 0xFFFF;               // Gửi dummy để tạo clock
            
            while (!(pSPIx->SR & (1 << 0))); // Wait until RXNE is set

            *pRxBuffer = pSPIx->DR;
            pRxBuffer++;
            Len--;
        }
    }

    // Đợi SPI không bận nữa
    while (pSPIx->SR & (1 << 7)); // BSY bit
}

#define SPI_CR1_SPE     (1 << 6)

void SPI_PeripheralControl(SPI_RegDef *pSPIx, uint8_t STATE) {
    if (STATE == ENABLE) {
        pSPIx->CR1 |= SPI_CR1_SPE;
    } else {
        pSPIx->CR1 &= ~SPI_CR1_SPE;
    }
}
void SPI_SSOEConfig(SPI_RegDef*pSPIx,uint8_t STATE){
    if(STATE == ENABLE){
        pSPIx->CR2 |= (1 << 2);
    }
    else {
        pSPIx->CR2 &= ~(1 << 2);
    }
}

void SPI_SendDataIT(SPI_Handle_T*pSPI_Handle,uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveDataIT(SPI_Handle_T*pSPI_Handle,uint8_t *pRxBuffer, uint32_t Len);

void SPI_IRQInterruptCfg(uint8_t IRQNum, uint8_t State);
void SPI_IRQPriorityCfg(uint8_t IRQNum, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_T*pSPI_Handle);