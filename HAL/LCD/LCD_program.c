#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <util/delay.h>

void LCD_voidSendCommand(u8 command)
{
    DIO_voidSetPinValue(PORT_CONTROL, RS, LOW);
    DIO_voidSetPinValue(PORT_CONTROL, RW, LOW);
#if LCD_MODE == LCD_8BIT
    DIO_voidSetPortValue(PORT_DATA, command);
#else
    DIO_voidSetPortValue(PORT_DATA, command);
    DIO_voidSetPinValue(PORT_CONTROL, E, HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(PORT_CONTROL, E, LOW);
    _delay_ms(2);
    DIO_voidSetPortValue(PORT_DATA, (command << 4));
#endif
    DIO_voidSetPinValue(PORT_CONTROL, E, HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(PORT_CONTROL, E, LOW);
    _delay_ms(2);
}

void LCD_voidSendChar(u8 Char)
{
    DIO_voidSetPinValue(PORT_CONTROL, RS, HIGH);
    DIO_voidSetPinValue(PORT_CONTROL, RW, LOW);
#if LCD_MODE == LCD_8BIT
    DIO_voidSetPortValue(PORT_DATA, Char);
#else
    DIO_voidSetPortValue(PORT_DATA, Char);
    DIO_voidSetPinValue(PORT_CONTROL, E, HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(PORT_CONTROL, E, LOW);
    _delay_ms(2);
    DIO_voidSetPortValue(PORT_DATA, (Char << 4));
#endif
    DIO_voidSetPinValue(PORT_CONTROL, E, HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(PORT_CONTROL, E, LOW);
    _delay_ms(2);
}

void LCD_voidInit()
{
    DIO_voidSetPortDirection(PORT_DATA, ALL_OUTPUT);
    DIO_voidSetPinDirection(PORT_CONTROL, RS, OUTPUT);
    DIO_voidSetPinDirection(PORT_CONTROL, RW, OUTPUT);
    DIO_voidSetPinDirection(PORT_CONTROL, E, OUTPUT);
    _delay_ms(32);
#if LCD_MODE == LCD_8BIT
    LCD_voidSendCommand(functionSet8Bit);
#else
    LCD_voidSendCommand(returnHome);
    LCD_voidSendCommand(functionSet4Bit);
#endif
    _delay_us(42);
    LCD_voidSendCommand(displayOn);
    _delay_us(42);
    LCD_voidSendCommand(clearDisplay);
    _delay_ms(2);
    LCD_voidSendCommand(entryMode);
}

void LCD_voidSendString(u8 *string)
{
    u8 i = 0;
    while (string[i] != '\0')
    {
        LCD_voidSendChar(string[i]);
        i++;
    }
}

void LCD_voidSendNumber(u16 number)
{
    u8 numOfDigits = 0, i;
    u16 n = number;
    while (n > 0)
    {
        numOfDigits++;
        n /= 10;
    }
    for (i = numOfDigits - 1; i >= 0; i--)
    {
        u8 j;
        u16 pow = 1;
        for (j = 1; j <= i; j++)
        {
            pow *= 10;
        }
        LCD_voidSendChar(ASCII_NUMBERS_START + number / pow);
        number %= pow;
    }
}

void LCD_voidSetCursorPosition(u8 position)
{
    u8 i;
    for (i = 1; i <= position; i++)
    {
        LCD_voidSendCommand(cursorShiftRight);
    }
}