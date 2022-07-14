#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

#include "STD_TYPES.h"

void SSD_voidInit(u8 portNumber);

void SSD_voidDisplayNumber(u8 portNumber, u8 Number);

void SSD_voidDisplayCounter(u8 portNumber, u8 Delay);

#endif