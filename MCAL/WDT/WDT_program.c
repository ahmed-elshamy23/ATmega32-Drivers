#include "BIT_MATH.h"
#include "WDT_interface.h"
#include "WDT_private.h"

void WDT_voidEnable()
{
    SET_BIT(WDTCR, WDE);
}

void WDT_voidDisable()
{
    WDTCR = ((1 << WDE) | (1 << WDTOE));
    WDTCR = 0;
}

void WDT_voidRefresh()
{
    asm("wdr");
}

void WDT_voidSleep(u8 prescaler)
{
    if (prescaler == 16)
    {
        CLR_BIT(WDTCR, WDP0);
        CLR_BIT(WDTCR, WDP1);
        CLR_BIT(WDTCR, WDP2);
    }
    else if (prescaler == 32)
    {
        SET_BIT(WDTCR, WDP0);
        CLR_BIT(WDTCR, WDP1);
        CLR_BIT(WDTCR, WDP2);
    }
    else if (prescaler == 64)
    {
        CLR_BIT(WDTCR, WDP0);
        SET_BIT(WDTCR, WDP1);
        CLR_BIT(WDTCR, WDP2);
    }
    else if (prescaler == 128)
    {
        SET_BIT(WDTCR, WDP0);
        SET_BIT(WDTCR, WDP1);
        CLR_BIT(WDTCR, WDP2);
    }
    else if (prescaler == 256)
    {
        CLR_BIT(WDTCR, WDP0);
        CLR_BIT(WDTCR, WDP1);
        SET_BIT(WDTCR, WDP2);
    }
    else if (prescaler == 512)
    {
        SET_BIT(WDTCR, WDP0);
        CLR_BIT(WDTCR, WDP1);
        SET_BIT(WDTCR, WDP2);
    }
    else if (prescaler == 1024)
    {
        CLR_BIT(WDTCR, WDP0);
        SET_BIT(WDTCR, WDP1);
        SET_BIT(WDTCR, WDP2);
    }
    else
    {
        SET_BIT(WDTCR, WDP0);
        SET_BIT(WDTCR, WDP1);
        SET_BIT(WDTCR, WDP2);
    }
}