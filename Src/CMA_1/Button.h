#ifndef __Button_H
#define __Button_H

#ifndef __CMA_MAIN_H
#error "This file should not be included directly. Include __CMA_MAIN_H instead."
#endif
#include <EasyButton.h>

#define button_left_pin    39
#define button_right_pin  34
#define buttonExitPin   36
#define button_ok_pin   35
#define buttonErrorPin    0
#define pinPower      32
#define pinReadPower    25

EasyButton button_right(button_right_pin, 50, true);
EasyButton button_ok(button_ok_pin, 50, true);
EasyButton buttonExit(buttonExitPin, 50, true);
void Check_button(void* pvParameters);



#endif
