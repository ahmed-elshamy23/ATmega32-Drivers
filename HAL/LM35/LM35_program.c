#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "LM35_interface.h"

void LM35_voidInit(u8 ADC_channel)
{
    ADC_voidInit(ADC_channel);
}

u8 LM35_u8GetTemperature()
{
    f32 ADC_result = ADC_f32GetResult();
    return ADC_result * 100;
}