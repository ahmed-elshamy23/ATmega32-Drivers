#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "SSD_config.h"
#include "SSD_interface.h"
#include "util/delay.h"

u8 Numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SSD_voidInit(u8 portNumber)
{
    DIO_voidSetPortDirection(portNumber, ALL_OUTPUT);
}

void SSD_voidDisplayNumber(u8 portNumber, u8 Number)
{
#if SSD_MODE == COMMON_CATHODE
    DIO_voidSetPortValue(portNumber, ~Numbers[Number]);
#else
    DIO_voidSetPortValue(portNumber, Numbers[Number]);
#endif
}

void SSD_voidDisplayCounter(u8 portNumber, u8 Delay)
{
    u8 i = 0;
    for (; i < 10; i++)
    {
        SSD_voidDisplayNumber(portNumber, i);
        _delay_ms(Delay);
    }
}