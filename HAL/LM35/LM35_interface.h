#ifndef LM32_INTERFACE_H
#define LM32_INTERFACE_H

#include "STD_TYPES.h"

void LM35_voidInit(u8 ADC_channel);

u16 LM35_u16GetTemperature();

#endif