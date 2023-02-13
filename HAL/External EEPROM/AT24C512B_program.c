#include "TWI_interface.h"
#include "TWI_private.h"
#include "AT24C512B_interface.h"
#include "AT24C512B_config.h"

void AT24C512B_voidInit()
{
    TWI_voidInit();
}

void AT24C512B_voidStopOperation()
{
    TWI_voidSendStopCondition();
}

void AT24C512B_voidWriteByte(u8 data, u8 firstWordAddress)
{
    TWI_voidSendStartCondition();
    TWI_voidMasterWrite(firstWordAddress, DEVICE_ADDRESS);
    TWI_voidMasterWrite(data, firstWordAddress);
    TWI_voidSendStopCondition();
}

u8 AT24C512B_u8ReadByte()
{
    TWI_voidSendStartCondition();
    TWI_voidMasterWrite(0, DEVICE_ADDRESS);
    TWI_voidMasterWrite(0xFF, 0);
    TWI_voidSendStartCondition();
    return TWI_u8MasterRead(DEVICE_ADDRESS);
}