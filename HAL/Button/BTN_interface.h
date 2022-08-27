#ifndef BTN_INTERFACE_H
#define BTN_INTERFACE_H

#include "STD_TYPES.h"

void BTN_voidInit(u8 portNumber, u8 pinNumber);

u8 BTN_u8ButtonIsPressed(u8 portNumber, u8 pinNumber);

#endif