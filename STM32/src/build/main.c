#include "stm32_gpio.h"
#include "stm32_spi.h"
#include "string.h"

void SPI_setup()
{
    SPI_Handle_T SPI_;
    SPI_.SPIx = SPI2;
    SPI_.SPI.SPI_DeviceMode = MASTER;
    SPI_.SPI.SPI_BusConfig = FULL_DUPLEX;
    SPI_.SPI.SPI_ClkSpeed = SPEED_DIV2;
    SPI_.SPI.SPI_DFF = DFF_8BITS;
    SPI_.SPI.SPI_CPHA = HIGH;
    SPI_.SPI.SPI_CPOL = LOW;
    SPI_.SPI.SPI_SSM = ENABLE;
    SPI_Init(&SPI_);
}


void SPI_Test(void)
{
    /*
     *PB12- SPI2_NSS
     *PB13- SPI2_SCK
     *PB14- SPI2_MISO
     *PB15- SPI2_MOSI
     */
    PinMode(GPIOB, 12, GPIO_MODE_AF_PP);
    PinMode(GPIOB, 13, GPIO_MODE_AF_PP);
    PinMode(GPIOB, 14, GPIO_MODE_AF_PP);
    PinMode(GPIOB, 15, GPIO_MODE_AF_PP);

    char tx[] = "HELLO WORLD";

    SPI_setup();
    SPI_PeripheralControl(SPI2, ENABLE);
    SPI_SendData(SPI2,(uint8_t*)tx,strlen(tx));
}

int main(void)
{
    

    while (1)
    {
        //   GPIO_Test();
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
