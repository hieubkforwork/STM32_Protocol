#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stm32_gpio.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern int button1_flag;

void getKeyInput();

#endif /* INC_BUTTON_H_ */

