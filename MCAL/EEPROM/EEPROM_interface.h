#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "STD_TYPES.h"

u8 EEPROM_voidReadByte(u16 address);

void EEPROM_voidWriteByte(u16 address, u8 data);

#endif