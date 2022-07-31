#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GIE_interface.h"

void GIE_voidEnable()
{
    SET_BIT(SREG, GENERAL_INTERRUPT);
}

void GIE_voidDisable()
{
    CLR_BIT(SREG, GENERAL_INTERRUPT);
}