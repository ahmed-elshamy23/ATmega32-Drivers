#include "DIO_interface.h"
#include "BUZZ_interface.h"

void BUZZ_voidInit(u8 portNumber, u8 pinNumber)
{
    DIO_voidSetPinDirection(portNumber, pinNumber, OUTPUT);
    DIO_voidSetPinValue(portNumber, pinNumber, LOW);
}

void BUZZ_voidMode(u8 portNumber, u8 pinNumber, u8 mode)
{
    DIO_voidSetPinValue(portNumber, pinNumber, mode);
}