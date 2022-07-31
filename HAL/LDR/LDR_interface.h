#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H

#include "STD_TYPES.h"

#define RESISTANCE 1000

void LDR_voidInit(u8 ADC_channel);

u32 LDR_u16GetResistance();

#endif