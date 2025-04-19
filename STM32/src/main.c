#include "stm32_gpio.h"

void GPIO_Test(void)
{
    digitalWrite(GPIOD, 2, LOW); // LED luôn sáng ban đầu
}
// Hàm chính
int main(void)
{
    PinMode(GPIOD, 2, OUTPUT);
    PinMode(GPIOC, 1, IT);
    while (1)
    {
        //   GPIO_Test();
    }
    return 0;
}

// EXTI
// void EXTI0_IRQHandler(void){}
void EXTI1_IRQHandler(void)
{
    NVIC_IRQHandling(1);
    delay_ms(20); // thời gian debounce
    // Debounce lần đầu
    delay_ms(20);
    if (digitalRead(GPIOC, 1) == 0)
    { // PRESSED_STATE = 0
        // Đợi thêm để phát hiện nhấn đè
        uint32_t hold_time = 0;
        while (digitalRead(GPIOC, 1) == 0)
        {
            delay_ms(10);
            hold_time += 10;
            if (hold_time >= 5000)
            {
                // Xử lý nhấn đè
                // Ví dụ: bật LED
                digitalWrite(GPIOD, 2, LOW);
                return;
            }
        }

        // Nếu thoát vòng lặp sớm => chỉ là nhấn ngắn
        TogglePin(GPIOD, 2); // Nhấn thường: đổi trạng thái LED
    }
}
// Tắt LED khi có ngắt

// void EXTI2_IRQHandler(void){}
// void EXTI3_IRQHandler(void){}
// void EXTI9_5_IRQHandler(void){}
// void EXTI15_10_IRQHandler(void){}
