#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H

#include "STD_TYPES.h"

void LM35_voidInit(u8 ADC_channel);

u8 LM35_u8GetTemperature();

#endif