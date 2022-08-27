#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "STD_TYPES.h"

void ADC_voidInit(u8 channel);

void ADC_voidStartConversion();

void ADC_voidInterruptEnable();

f32 ADC_f32GetResult();

void ADC_voidSetCallback(void (*ptr)());

void ADC_VECT(void) __attribute__((signal));

#endif