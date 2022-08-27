#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "BIT_MATH.h"

u8 EEPROM_voidReadByte(u16 address)
{
    while (GET_BIT(EECR, EEWE))
        ;
    EEAR = address;
    SET_BIT(EECR, EERE);
    return EEDR;
}

void EEPROM_voidWriteByte(u16 address, u8 data)
{
    while (GET_BIT(EECR, EEWE))
        ;
    EEAR = address;
    EEDR = data;
    SET_BIT(EECR, EEMWE);
    SET_BIT(EECR, EEWE);
}