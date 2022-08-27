#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "BTN_interface.h"

void BTN_voidInit(u8 portNumber, u8 pinNumber)
{
    DIO_voidSetPinDirection(portNumber, pinNumber, INPUT);
    DIO_voidSetPinValue(portNumber, pinNumber, HIGH);
}

u8 BTN_u8ButtonIsPressed(u8 portNumber, u8 pinNumber)
{
    if (DIO_u8GetPinValue(portNumber, pinNumber) == LOW)
        return 0x01;
    return 0;
}