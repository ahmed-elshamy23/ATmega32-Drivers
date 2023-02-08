#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "STD_TYPES.h"

void SPI_voidInit();

void SPI_voidSendData(u8 data);

u8 SPI_u8ReceiveData();

void SPI_voidSendString(u8 *string);

void SPI_voidReceiveString(u8 *string, u8 terminateCharacter);

void SPI_voidInterruptEnable();

void SPI_voidInterruptDisable();

void SPI_voidSetCallback(void (*ptr)());

void SPI_ISR() __attribute__((signal));

#endif