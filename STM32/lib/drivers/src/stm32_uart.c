#include"stm32_uart.h"



void USART_PeriClockControl(USART_RegDef*pUSARTx, uint8_t STATE){
    if(STATE == ENABLE) {
        if(pUSARTx == USART1) {USART1_PCLK_EN();}
        else if(pUSARTx == USART2){USART2_PCLK_EN();}
        else if(pUSARTx == USART3){USART3_PCLK_EN();}
        else if(pUSARTx == UART4){UART4_PCLK_EN();}
        else if(pUSARTx == UART5){UART5_PCLK_EN();}

    }
}
void USART_Init(USART_Handle_T *pUSART_Handle){

    uint32_t temp = 0;
    USART_PeriClockControl(pUSART_Handle->pUSARTx, ENABLE);

    /*CONFIG CR1*/
    //mode
    if(pUSART_Handle->USART_Config.USART_MODE == USART_MODE_RX) temp |= (1 << 2);
    else if(pUSART_Handle->USART_Config.USART_MODE == USART_MODE_TX) temp |= (1 << 3);
    else if(pUSART_Handle->USART_Config.USART_MODE == USART_MODE_TXRX) temp |= ((1 << 2)|(1 << 3));
    //length
    temp |= (pUSART_Handle->USART_Config.USART_WordLength << 12);
    //parity
    if(pUSART_Handle->USART_Config.USART_ParityBit == USART_PARITY_EVEN){
        temp |= (1 << 10);  //PCE EN
        temp &=~ (1 << 9);  //EVEN
    }
    else if(pUSART_Handle->USART_Config.USART_ParityBit == USART_PARITY_ODD){
        temp |= (1 << 10);  //PCE EN
        temp |= (1 << 9);  //EVEN
    }
    else temp &=~ (1 << 10);  //PCE DIS

    pUSART_Handle->pUSARTx->CR1 = temp;
    /*END CONFIG CR1*/

    /*CONFIG CR2*/
    temp = 0;
    temp |= (pUSART_Handle->USART_Config.USART_NoOfStopBits << 12);
    pUSART_Handle->pUSARTx->CR2 = temp;
    /*END CONFIG CR2*/
    
    /*CONFIG CR3*/
    temp=0;
    if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOWCTR_CTSE){
        temp |= (1 << 9);
        temp &=~ (1 << 8);
    }
    else if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOWCTR_RTSE){
        temp |= (1 << 8);
        temp &=~ (1 << 9);
    }
    else if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOWCTR_CTSE_RTSE){
        temp |= (1 << 8);
        temp |= (1 << 9);
    }
    else {
        temp &=~ (1 << 8);
        temp &=~ (1 << 9);
    }
    pUSART_Handle->pUSARTx->CR3 = temp;

    /*END CONFIG CR3*/

    USART_SetBaud(pUSART_Handle->pUSARTx, pUSART_Handle->USART_Config.USART_BAUD);
    USART_PeriControl(USART2,ENABLE);

 }


uint8_t USART_GetFlag(USART_RegDef*pUSARTx, uint8_t statusflagname){
    if(pUSARTx->SR & statusflagname) return 1;
    else return 0;
}
void USART_ClearFlag(USART_RegDef*pUSARTx, uint16_t statusflagname);
void USART_PeriControl(USART_RegDef*pUSARTx, uint8_t STATE){
    if(STATE == ENABLE){
        pUSARTx->CR1 |= (1<<13);    
    }
    else pUSARTx->CR1 &=~ (1<<13);  
}
void USART_SetBaud(USART_RegDef*pUSARTx, uint32_t BaudRate){
    uint32_t PCLKx;
    uint32_t uart_div;
    uint32_t Mantisa, Fraction;

    if(pUSARTx == USART1){
        //APB2
        PCLKx = RCC_GetPCLK2Value();
    }
    else{
        //APB1
        PCLKx = RCC_GetPCLK1Value();
    }
    uart_div = ((25 * PCLKx) / (4 * BaudRate)); // Over sampling 16x cố định
    Mantisa = uart_div /100;
    Fraction = (((uart_div - (Mantisa * 100)) * 16) + 50) / 100; 
    pUSARTx->BRR = (Mantisa << 4) | (Fraction & 0xF);

}

 


void USART_SendData(USART_Handle_T *pUSART_Handle, uint8_t*pTxBuffer, uint32_t Len){
    uint16_t *pdata;
    for(uint32_t i = 0; i < Len; i++){
        while (!USART_GetFlag(pUSART_Handle->pUSARTx,USART_FLAG_TXE));// Wait until TX Flag is set in SR
        if(pUSART_Handle->USART_Config.USART_WordLength == USART_LEN_9BITS){ //9BITS
            pdata = (uint16_t*) pTxBuffer;
            pUSART_Handle->pUSARTx->DR=(*pdata & (uint16_t)0x01FF);

            if(pUSART_Handle->USART_Config.USART_ParityBit == USART_PARITY_NONE){
                pTxBuffer++;
                pTxBuffer++;
            }
            else{
                pTxBuffer++;
            }
        }
        else{ //8BITS
            if(pUSART_Handle->USART_Config.USART_ParityBit == USART_PARITY_NONE){
                pUSART_Handle->pUSARTx->DR=(*pTxBuffer & (uint8_t)0xFF);
                pTxBuffer++;
            }
            else {
                pUSART_Handle->pUSARTx->DR=(*pTxBuffer & (uint8_t)0x7F);
                pTxBuffer++;
            }
        }
       
        
    }

    while(!USART_GetFlag(pUSART_Handle->pUSARTx,USART_FLAG_TC));
}


void USART_ReceiveData(USART_Handle_T *pUSART_Handle, uint8_t *pRxBuffer, uint32_t Len){
    for(uint32_t i = 0; i < Len; i++){
        while(!USART_GetFlag(pUSART_Handle->pUSARTx, USART_FLAG_RXNE)); // Wait until RXNE is set

        if(pUSART_Handle->USART_Config.USART_WordLength == USART_LEN_9BITS){
            if(pUSART_Handle->USART_Config.USART_ParityBit == USART_PARITY_NONE){
                *((uint16_t*) pRxBuffer) = pUSART_Handle->pUSARTx->DR & (uint16_t)0x01FF;
                pRxBuffer += 2;
            } else {
                *pRxBuffer = pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF;
                pRxBuffer++;
            }
        } else { // 8-bit data
            if(pUSART_Handle->USART_Config.USART_ParityBit == USART_PARITY_NONE){
                *pRxBuffer = (uint8_t)(pUSART_Handle->pUSARTx->DR & 0xFF);
            } else {
                *pRxBuffer = (uint8_t)(pUSART_Handle->pUSARTx->DR & 0x7F); // 7 bits data + 1 bit parity
            }
            pRxBuffer++;
        }
    }
}


void USART_SendDataIT(USART_Handle_T *pUSART_Handle, uint8_t*pTxBuffer, uint32_t Len);
void USART_ReceiveDataIT(USART_Handle_T *pUSART_Handle, uint8_t*pRxBuffer, uint32_t Len);
void USART_DeInit(USART_Handle_T *pUSART_Handle);
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t STATE);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_T *pUSART_Handle);