#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "STD_TYPES.h"

#define ON 0
#define OFF 1

void LED_voidInit(u8 portNumber, u8 pinNumber);
void LED_voidOnOff(u8 portNumber, u8 pinNumber, u8 value);
void LED_voidToggle(u8 portNumber, u8 pinNumber);

#endif