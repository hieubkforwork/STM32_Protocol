#ifndef INC_STM32_UART_H_  
#define INC_STM32_UART_H_ 

#include"stm32f1.h"
#include"stm32_rcc.h"
typedef struct USART_Config_T
{
    uint8_t USART_MODE;
    uint32_t USART_BAUD;
    uint8_t USART_NoOfStopBits;
    uint8_t USART_WordLength;
    uint8_t USART_ParityBit;
    uint8_t USART_HWFlowControl;

}USART_Config_T;


typedef struct USART_Handle_T
{
    USART_RegDef *pUSARTx;
    USART_Config_T USART_Config;
    uint8_t * pTxBuffer;
    uint8_t * pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxBusy;
    uint8_t RxBusy;
}USART_Handle_T;


#define USART_MODE_TX 0
#define USART_MODE_RX 1
#define USART_MODE_TXRX 2

#define USART_BAUD_2400 2400
#define USART_BAUD_9600 9600
#define USART_BAUD_19200 19200
#define USART_BAUD_57600 57600
#define USART_BAUD_115200 115200
#define USART_BAUD_230400 230400
#define USART_BAUD_460800 460800
#define USART_BAUD_921600 921600
#define USART_BAUD_2250000 2250000
#define USART_BAUD_4500000 4500000

#define USART_STOP_1BIT 0x0
#define USART_STOP_0_5BIT 0x1
#define USART_STOP_2BIT 0x2
#define USART_STOP_1_5BIT 0x3
// 0.5 và 1.5 không được dùng cho UART4 và UART5

#define USART_LEN_8BITS 0
#define USART_LEN_9BITS 1

#define USART_PARITY_ODD 2
#define USART_PARITY_EVEN 1
#define USART_PARITY_NONE 0

#define USART_HW_FLOWCTR_NONE 0
#define USART_HW_FLOWCTR_CTSE 1
#define USART_HW_FLOWCTR_RTSE 2
#define USART_HW_FLOWCTR_CTSE_RTSE 3

#define USART_FLAG_TXE (1<<7)
#define USART_FLAG_RXNE (1<<5)
#define USART_FLAG_TC (1<<6)

#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_BUSY_IN_NONE 0



void USART_PeriClockControl(USART_RegDef*pUSARTx, uint8_t STATE);
void USART_Init(USART_Handle_T *pUSART_Handle);
void USART_DeInit(USART_Handle_T *pUSART_Handle);

void USART_SendData(USART_Handle_T *pUSART_Handle, uint8_t*pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_T *pUSART_Handle, uint8_t*pRxBuffer, uint32_t Len);

void USART_SendDataIT(USART_Handle_T *pUSART_Handle, uint8_t*pTxBuffer, uint32_t Len);
void USART_ReceiveDataIT(USART_Handle_T *pUSART_Handle, uint8_t*pRxBuffer, uint32_t Len);

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t STATE);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_T *pUSART_Handle);

uint8_t USART_GetFlag(USART_RegDef*pUSARTx, uint8_t statusflagname);
void USART_ClearFlag(USART_RegDef*pUSARTx, uint16_t statusflagname);
void USART_PeriControl(USART_RegDef*pUSARTx, uint8_t STATE);
void USART_SetBaud(USART_RegDef*pUSARTx, uint32_t BaudRate);

#endif