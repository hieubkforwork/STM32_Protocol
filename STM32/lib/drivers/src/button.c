#include "button.h"

int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE;

int TimeOutForKeyPress =  500;
int button1_pressed = 0;
int button1_long_pressed = 0;
int button1_flag = 0;

void getKeyInput() {
 KeyReg2 = KeyReg1;
 KeyReg1 = KeyReg0;
 // Reading button status (add your key)
 KeyReg0 = digitalRead(GPIOC,1);

 if ((KeyReg1 == KeyReg0) && (KeyReg1 == KeyReg2)) {
   if (KeyReg2 != KeyReg3) {
     KeyReg3 = KeyReg2;
     if (KeyReg3 == PRESSED_STATE) {
       TimeOutForKeyPress = 2;  // Reset timeout for long press detection
       button1_flag = 1;          // Set button flag to indicate button press
     }
   } else {
     TimeOutForKeyPress--;
     if (TimeOutForKeyPress == 0) {
       TimeOutForKeyPress = 2;  // Reset timeout
       if (KeyReg3 == PRESSED_STATE) {
         button1_long_pressed = 1; // Long press detected
         button1_flag = 0;         // Clear regular press flag
       }
     }
   }
 }
}
