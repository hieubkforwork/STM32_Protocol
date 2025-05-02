#include "stm32_gpio.h"
#include "stm32_spi.h"
#include "stm32_uart.h"
#include "string.h"


SPI_Handle_T SPI_;
void SPI_setup()
{
    SPI_.SPIx = SPI2;
    SPI_.SPI.SPI_DeviceMode = MASTER;
    SPI_.SPI.SPI_BusConfig = FULL_DUPLEX;
    SPI_.SPI.SPI_ClkSpeed = SPEED_DIV256;     // tốc độ nhanh hơn một chút
    SPI_.SPI.SPI_DFF = DFF_8BITS;
    SPI_.SPI.SPI_CPHA = LOW;                // SỬA
    SPI_.SPI.SPI_CPOL = LOW;                // GIỮ
    SPI_.SPI.SPI_SSM = DISABLE;
    SPI_Init(&SPI_);
}

USART_Handle_T USART_;
void USART_setup()
{
    USART_.pUSARTx = USART2;
    USART_.USART_Config.USART_MODE=USART_MODE_TXRX;
    USART_.USART_Config.USART_HWFlowControl = USART_HW_FLOWCTR_NONE;
    USART_.USART_Config.USART_NoOfStopBits = USART_STOP_1BIT;     
    USART_.USART_Config.USART_ParityBit = USART_PARITY_NONE;
    USART_.USART_Config.USART_WordLength =USART_LEN_8BITS;              
    USART_.USART_Config.USART_BAUD = USART_BAUD_9600;              
    USART_Init(&USART_);
}


// void SPI_Test(void)
// {
//     /*
//      *PB12- SPI2_NSS
//      *PB13- SPI2_SCK
//      *PB14- SPI2_MISO
//      *PB15- SPI2_MOSI
//      */
//     PinMode(GPIOB, 12, GPIO_MODE_AF_PP);
//     PinMode(GPIOB, 13, GPIO_MODE_AF_PP);
//     PinMode(GPIOB, 14, GPIO_MODE_AF_PP);
//     PinMode(GPIOB, 15, GPIO_MODE_AF_PP);

    

//     SPI_setup();
//     SPI_PeripheralControl(SPI2, ENABLE);
//     SPI_SSOEConfig(SPI2,ENABLE);
// }


void UART_Test(void){
    /*PA2 : TX
      PA3 : RX
    */
   PinMode(GPIOA,2,ALT);
   PinMode(GPIOA,3,INPUT);
   USART_setup();

}
int main(void)
{
    UART_Test(); // Initialize UART

    uint8_t test_data[] = "USART READY\r\n";
    uint8_t rx_byte;
    uint8_t rx_buf[64];
    uint32_t i = 0;

    USART_SendData(&USART_, test_data, strlen((char*)test_data));

    while (1)
    {
        // Receive 1 byte at a time
        USART_ReceiveData(&USART_, &rx_byte, 1);

        // Echo back if newline received
        if (rx_byte == '\r' || rx_byte == '\n') {
            rx_buf[i++] = '\r';  // Add carriage return
            rx_buf[i++] = '\n';  // Add newline
            USART_SendData(&USART_, rx_buf, i);  // Send full line
            i = 0;  // Reset buffer index
        }
        else {
            if (i < sizeof(rx_buf) - 2) { // Leave space for \r\n
                rx_buf[i++] = rx_byte;
            } else {
                // Buffer overflow protection
                i = 0;
            }
        }
    }

    return 0;
}

// EXTI
// void EXTI0_IRQHandler(void){}

// void EXTI1_IRQHandler(void)
// {
//     NVIC_IRQHandling(1);
//     delay_ms(20); // thời gian debounce
//     // Debounce lần đầu
//     delay_ms(20);
//     if (digitalRead(GPIOC, 1) == 0)
//     { // PRESSED_STATE = 0
//         // Đợi thêm để phát hiện nhấn đè
//         uint32_t hold_time = 0;
//         while (digitalRead(GPIOC, 1) == 0)
//         {
//             delay_ms(10);
//             hold_time += 10;
//             if (hold_time >= 5000)
//             {
//                 // Xử lý nhấn đè
//                 // Ví dụ: bật LED
//                 digitalWrite(GPIOD, 2, LOW);
//                 return;
//             }
//         }

//         // Nếu thoát vòng lặp sớm => chỉ là nhấn ngắn
//         TogglePin(GPIOD, 2); // Nhấn thường: đổi trạng thái LED
//     }
// }

// void EXTI2_IRQHandler(void){}
// void EXTI3_IRQHandler(void){}
// void EXTI9_5_IRQHandler(void){}
// void EXTI15_10_IRQHandler(void){}
