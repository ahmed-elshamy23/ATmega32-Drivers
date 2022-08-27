#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "STD_TYPES.h"

void DIO_voidSetPinDirection(u8 portNumber, u8 pinNumber, u8 direction);
void DIO_voidSetPortDirection(u8 portNumber, u8 direction);

void DIO_voidSetPinValue(u8 portNumber, u8 pinNumber, u8 value);
void DIO_voidSetPortValue(u8 portNumber, u8 value);

void DIO_voidTogglePin(u8 portNumber, u8 pinNumber);

u8 DIO_u8GetPinValue(u8 portNumber, u8 pinNumber);
u8 DIO_u8GetPortValue(u8 portNumber);

#endif