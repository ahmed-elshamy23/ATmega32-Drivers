#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

#include "STD_TYPES.h"

void TWI_voidInit();

void TWI_voidSetNodeAddress(u8 address);

void TWI_voidMasterWrite(u8 data, u8 address);

u8 TWI_u8MasterRead(u8 address);

void TWI_voidSlaveWrite(u8 data);

u8 TWI_u8SlaveRead();

void TWI_voidSendStartCondition();

void TWI_voidSendStopCondition();

void TWI_voidSendString(u8 *string, u8 address);

void TWI_voidReceiveString(u8 *string, u8 terminateCharacter);

void TWI_voidInterruptEnable();

void TWI_voidInterruptDisable();

void TWI_voidSetCallback(void (*ptr)());

void TWI_ISR() __attribute__((signal));

#endif