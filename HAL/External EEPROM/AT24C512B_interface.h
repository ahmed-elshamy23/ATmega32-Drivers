#ifndef AT24C512B_INTERFACE_H
#define AT24C512B_INTERFACE_H

#include "STD_TYPES.h"

void AT24C512B_voidInit();

void AT24C512B_voidStopOperation();

void AT24C512B_voidWriteByte(u8 data, u8 firstWordAddress);

u8 AT24C512B_u8ReadByte();

#endif