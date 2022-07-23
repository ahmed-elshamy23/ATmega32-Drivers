#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"

void LED_voidInit(u8 portNumber, u8 pinNumber)
{
    DIO_voidSetPinDirection(portNumber, pinNumber, OUTPUT);
    DIO_voidSetPinValue(portNumber, pinNumber, LOW);
}

void LED_voidOnOff(u8 portNumber, u8 pinNumber, u8 value)
{
    switch (value)
    {
    case ON:
        DIO_voidSetPinValue(portNumber, pinNumber, HIGH);
        break;
    case OFF:
        DIO_voidSetPinValue(portNumber, pinNumber, LOW);
    }
}

void LED_voidToggle(u8 portNumber, u8 pinNumber)
{
    DIO_voidTogglePin(portNumber, pinNumber);
}