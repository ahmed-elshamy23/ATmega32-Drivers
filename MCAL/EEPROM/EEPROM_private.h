#ifndef EEPROM_PRIVATE_H
#define EEPROM_PRIVATE_H

#include "STD_TYPES.h"

#define EEAR (*(volatile u16 *)(0x3E))
#define EEDR (*(volatile u8 *)(0x3D))
#define EECR (*(volatile u8 *)(0x3C))

#define EERE 0
#define EEWE 1
#define EEMWE 2
#define EERIE 3

#endif