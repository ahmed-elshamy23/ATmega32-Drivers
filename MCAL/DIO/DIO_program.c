#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"

void DIO_voidSetPinDirection(u8 portNumber, u8 pinNumber, u8 direction)
{
    switch (portNumber)
    {
    case PORTA:
        switch (direction)
        {
        case INPUT:
            CLR_BIT(DDRA_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(DDRA_REG, pinNumber);
        }
        break;
    case PORTB:
        switch (direction)
        {
        case INPUT:
            CLR_BIT(DDRB_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(DDRB_REG, pinNumber);
        }
        break;
    case PORTC:
        switch (direction)
        {
        case INPUT:
            CLR_BIT(DDRC_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(DDRC_REG, pinNumber);
        }
        break;
    case PORTD:
        switch (direction)
        {
        case INPUT:
            CLR_BIT(DDRD_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(DDRD_REG, pinNumber);
        }
    }
}

void DIO_voidSetPortDirection(u8 portNumber, u8 direction)
{
    switch (portNumber)
    {
    case PORTA:
        DDRA_REG = direction;
        break;
    case PORTB:
        DDRB_REG = direction;
        break;
    case PORTC:
        DDRC_REG = direction;
        break;
    case PORTD:
        DDRD_REG = direction;
    }
}

void DIO_voidSetPinValue(u8 portNumber, u8 pinNumber, u8 value)
{
    switch (portNumber)
    {
    case PORTA:
        switch (value)
        {
        case INPUT:
            CLR_BIT(PORTA_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(PORTA_REG, pinNumber);
        }
        break;
    case PORTB:
        switch (value)
        {
        case INPUT:
            CLR_BIT(PORTB_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(PORTB_REG, pinNumber);
        }
        break;
    case PORTC:
        switch (value)
        {
        case INPUT:
            CLR_BIT(PORTC_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(PORTC_REG, pinNumber);
        }
        break;
    case PORTD:
        switch (value)
        {
        case INPUT:
            CLR_BIT(PORTD_REG, pinNumber);
            break;
        case OUTPUT:
            SET_BIT(PORTD_REG, pinNumber);
        }
    }
}

void DIO_voidSetPortValue(u8 portNumber, u8 value)
{
    switch (portNumber)
    {
    case PORTA:
        PORTA_REG = value;
        break;
    case PORTB:
        PORTB_REG = value;
        break;
    case PORTC:
        PORTC_REG = value;
        break;
    case PORTD:
        PORTD_REG = value;
    }
}

void DIO_voidTogglePin(u8 portNumber, u8 pinNumber)
{
    switch (portNumber)
    {
    case PORTA:
        TOG_BIT(PORTA_REG, pinNumber);
        break;
    case PORTB:
        TOG_BIT(PORTB_REG, pinNumber);
        break;
    case PORTC:
        TOG_BIT(PORTC_REG, pinNumber);
        break;
    case PORTD:
        TOG_BIT(PORTD_REG, pinNumber);
    }
}

u8 DIO_u8GetPinValue(u8 portNumber, u8 pinNumber)
{
    u8 value = 0;
    switch (portNumber)
    {
    case PORTA:
        value = GET_BIT(PINA_REG, pinNumber);
        break;
    case PORTB:
        value = GET_BIT(PINB_REG, pinNumber);
        break;
    case PORTC:
        value = GET_BIT(PINC_REG, pinNumber);
        break;
    case PORTD:
        value = GET_BIT(PIND_REG, pinNumber);
    }
    return value;
}

u8 DIO_u8GetPortValue(u8 portNumber)
{
    u8 value = 0;
    switch (portNumber)
    {
    case PORTA:
        value = PINA_REG;
        break;
    case PORTB:
        value = PINB_REG;
        break;
    case PORTC:
        value = PINC_REG;
        break;
    case PORTD:
        value = PIND_REG;
    }
    return value;
}