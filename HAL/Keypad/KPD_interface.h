#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

#include "STD_TYPES.h"

#define R0 0
#define R1 1
#define R2 2
#define R3 3

#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define ROW_START 0
#define ROW_END 3
#define COL_START 4
#define COL_END 7

#define NOT_PRESSED 0xFF

void KPD_voidInit(u8 portNumber);

u8 KPD_u8GetPresseddKey(u8 portNumber);

#endif