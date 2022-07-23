#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LDR_interface.h"
#include "LDR_config.h"

void LDR_voidInit(u8 ADC_channel)
{
    ADC_voidInit(ADC_channel);
    ADC_voidStartConversion();
}

u16 LDR_u16GetResult()
{
    return (KNOWN_RESISTANCE * VIN - KNOWN_RESISTANCE * ADC_u16GetResult()) / ADC_u16GetResult();
}