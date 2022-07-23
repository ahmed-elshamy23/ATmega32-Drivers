#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXIT_interface.h"
#include "GIE_interface.h"

void (*callBackINT0)(void) = NULL;
void (*callBackINT1)(void) = NULL;
void (*callBackINT2)(void) = NULL;

void EXIT_voidInit(u8 peripheral, u8 mode)
{
    GIE_voidEnable();
    switch (peripheral)
    {
    case INT0:
        SET_BIT(GICR, INT0_BIT);
        switch (mode)
        {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, ISC00);
            CLR_BIT(MCUCR, ISC01);
            break;
        case ANY_CHANGE:
            SET_BIT(MCUCR, ISC00);
            CLR_BIT(MCUCR, ISC01);
            break;
        case FALLING_EDGE:
            CLR_BIT(MCUCR, ISC00);
            SET_BIT(MCUCR, ISC01);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, ISC00);
            SET_BIT(MCUCR, ISC01);
        }
        break;
    case INT1:
        SET_BIT(GICR, INT1_BIT);
        switch (mode)
        {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, ISC10);
            CLR_BIT(MCUCR, ISC11);
            break;
        case ANY_CHANGE:
            SET_BIT(MCUCR, ISC10);
            CLR_BIT(MCUCR, ISC11);
            break;
        case FALLING_EDGE:
            CLR_BIT(MCUCR, ISC10);
            SET_BIT(MCUCR, ISC11);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, ISC10);
            SET_BIT(MCUCR, ISC11);
        }
        break;
    case INT2:
        SET_BIT(GICR, INT2_BIT);
        switch (mode)
        {
        case FALLING_EDGE:
            CLR_BIT(MCUCSR, ISC2);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCSR, ISC2);
        }
    }
}

void EXIT_voidSetCallbackINT0(void (*ptr)())
{
    callBackINT0 = ptr;
}

void EXIT_voidSetCallbackINT1(void (*ptr)())
{
    callBackINT1 = ptr;
}

void EXIT_voidSetCallbackINT2(void (*ptr)())
{
    callBackINT2 = ptr;
}

void __vector_1(void)
{
    if (callBackINT0 != NULL)
    {
        callBackINT0();
    }
}

void __vector_2(void)
{
    if (callBackINT1 != NULL)
    {
        callBackINT1();
    }
}

void __vector_3(void)
{
    if (callBackINT2 != NULL)
    {
        callBackINT2();
    }
}