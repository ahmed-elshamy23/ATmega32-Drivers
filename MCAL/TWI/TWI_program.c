#include "BIT_MATH.h"
#include "TWI_private.h"
#include "TWI_interface.h"
#include "TWI_config.h"

static void (*callback)() = NULL;

void TWI_voidInit()
{
#if TWI_PRESCALER == TWI_PRESCALER_1
    CLR_BIT(TWSR, TWPS0);
    CLR_BIT(TWSR, TWPS1);
#elif TWI_PRESCALER == TWI_PRESCALER_4
    SET_BIT(TWSR, TWPS0);
    CLR_BIT(TWSR, TWPS1);
#elif TWI_PRESCALER == TWI_PRESCALER_16
    CLR_BIT(TWSR, TWPS0);
    SET_BIT(TWSR, TWPS1);
#elif TWI_PRESCALER == TWI_PRESCALER_64
    SET_BIT(TWSR, TWPS0);
    SET_BIT(TWSR, TWPS1);
#endif

#if TWI_GENERAL_CALL == TWI_GENERAL_CALL_ENABLE
    SET_BIT(TWAR, TWGCE);
#elif TWI_GENERAL_CALL == TWI_GENERAL_CALL_DISABLE
    CLR_BIT(TWAR, TWGCE);
#endif

    SET_BIT(TWCR, TWEN);
}

void TWI_voidSetNodeAddress(u8 address)
{
    TWAR = ((u16)address << 1) | GET_BIT(TWAR, TWGCE);
}

void TWI_voidMasterWrite(u8 data, u8 address)
{
    u8 TWCR_temp = 0;
    while (!GET_BIT(TWCR, TWINT))
        ;
    TWDR = ((u16)address << 1) | WRITE_BIT;
    TWCR_temp = 0;
    SET_BIT(TWCR_temp, TWINT);
    SET_BIT(TWCR_temp, TWEN);
    TWCR = TWCR_temp;
    while (!GET_BIT(TWCR, TWINT))
        ;
    TWDR = data;
    TWCR_temp = 0;
    SET_BIT(TWCR_temp, TWINT);
    SET_BIT(TWCR_temp, TWEN);
    TWCR = TWCR_temp;
    while (!GET_BIT(TWCR, TWINT))
        ;
}

u8 TWI_u8MasterRead(u8 address)
{
    u8 TWCR_temp = 0, receivedData = 0xFF;
    while (!GET_BIT(TWCR, TWINT))
        ;
    TWDR = ((u16)address << 1) | READ_BIT;
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWINT);
    TWCR = TWCR_temp;
    while (!GET_BIT(TWCR, TWINT))
        ;
    TWCR_temp = 0;
    receivedData = TWDR;
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWINT);
    SET_BIT(TWCR_temp, TWEA);
    TWCR = TWCR_temp;
    while (!GET_BIT(TWCR, TWINT))
        ;
    return receivedData;
}

void TWI_voidSlaveWrite(u8 data)
{
    TWCR = 0b11000100;
    u8 TWCR_temp = 0;
    while (!GET_BIT(TWCR, TWINT))
        ;
    TWDR = data;
    SET_BIT(TWCR_temp, TWEA);
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWINT);
    TWCR = TWCR_temp;
    while (!GET_BIT(TWCR, TWINT))
        ;
    TWCR_temp = 0;
    SET_BIT(TWCR_temp, TWEA);
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWINT);
    TWCR = TWCR_temp;
}

u8 TWI_u8SlaveRead()
{
    TWCR = 0b11000100;
    u8 receivedData = 0;
    u8 TWCR_temp = 0;
    while (!GET_BIT(TWCR, TWINT))
        ;
    receivedData = TWDR;
    SET_BIT(TWCR_temp, TWINT);
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWEA);
    TWCR = TWCR_temp;
    return receivedData;
}

void TWI_voidSendStartCondition()
{
    u8 TWCR_temp = 0;
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWINT);
    SET_BIT(TWCR_temp, TWSTA);
    TWCR = TWCR_temp;
}

void TWI_voidSendStopCondition()
{
    u8 TWCR_temp = 0;
    SET_BIT(TWCR_temp, TWEN);
    SET_BIT(TWCR_temp, TWINT);
    SET_BIT(TWCR_temp, TWSTO);
    TWCR = TWCR_temp;
}

void TWI_voidSendString(u8 *string, u8 address)
{
    u8 i = 0;
    while (string[i] != '\0')
    {
        TWI_voidMasterWrite(string[i], address);
        i++;
    }
}

void TWI_voidReceiveString(u8 *string, u8 terminateCharacter)
{
    u8 i = 0;
    do
    {
        string[i] = TWI_u8SlaveRead();
        i++;
    } while (string[i - 1] != terminateCharacter);
    string[i - 1] = '\0';
}

void TWI_voidInterruptEnable()
{
    SET_BIT(TWCR, TWIE);
}

void TWI_voidInterruptDisable()
{
    CLR_BIT(TWCR, TWIE);
}

void TWI_voidSetCallback(void (*ptr)())
{
    callback = ptr;
}

void TWI_ISR()
{
    if (callback != NULL)
        callback();
}