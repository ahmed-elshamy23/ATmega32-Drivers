#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

#include "STD_TYPES.h"

#define NOT_PRESSED 0xFF

void KPD_voidInit(u8 portNumber);

u8 KPD_u8GetPressedKey(u8 portNumber);

#endif