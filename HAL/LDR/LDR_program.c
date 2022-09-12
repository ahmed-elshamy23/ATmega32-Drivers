#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "LDR_interface.h"

void LDR_voidInit(u8 ADC_channel)
{
    ADC_voidInit(ADC_channel);
}

u32 LDR_u16GetResistance()
{
    f32 ADC_result = ADC_f32GetResult();
    return (RESISTANCE * 5.0f - RESISTANCE * ADC_result) / ADC_result;
}