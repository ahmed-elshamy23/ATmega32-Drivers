#include "ADC_config.h"
#include "ADC_interface.h"
#include "LM35_interface.h"

void LM35_voidInit(u8 ADC_channel)
{
    ADC_voidInit(ADC_channel);
    ADC_voidStartConversion();
}

u16 LM35_u16GetTemperature()
{
    return (ADC_u16GetResult() * 0.49);
}