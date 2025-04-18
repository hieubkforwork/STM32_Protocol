#include"stm32f1.h"
#include "stm32_gpio.h"
#include<stdint.h>
// Hàm kiểm tra GPIO output
void GPIO_Test(void) {
    // Bật đồng hồ cho các GPIO
    
    // Cấu hình PA5 là output
    GPIO_Handle_T GPIO_Handle;
    GPIO_Handle.pGPIOx = GPIOD;  // Chọn GPIOA
    GPIO_Handle.GPIO_PIN.GPIO_PinNumber = 2;  // Chọn chân PA5
    GPIO_Handle.GPIO_PIN.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;  // Chế độ Output
    GPIO_Handle.GPIO_PIN.GPIO_PinSpeed = GPIO_SPEED_10MHZ;  // Tốc độ trung bình
    GPIO_Handle.GPIO_PIN.GPIO_PinPull = GPIO_NOPULL;  // Không dùng pull-up/pull-down

    // Cấu hình GPIO
    GPIO_Init(&GPIO_Handle);

    // Bật chân PA5 (LED sáng)
    digitalWrite(GPIOD, 2, LOW);
    delay_s(1);
    // Tắt chân PA5 (LED tắt)
    digitalWrite(GPIOD, 2, HIGH);
    delay_s(1);

}



// Hàm chính
int main(void) {
    

    // Kiểm tra GPIO output (Bật/Tắt LED)
    while (1) {
        GPIO_Test();
    }

    // Kiểm tra GPIO input (Bật/Tắt LED theo trạng thái công tắc)
    // while (1) {
    //     GPIO_InputTest();
    // }

    return 0;
}
