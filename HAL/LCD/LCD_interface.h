#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "STD_TYPES.h"

#define LCD_8BIT 0
#define LCD_4BIT 1

#define ASCII_NUMBERS_START 48

#define clearDisplay 0x01
#define returnHome 0x02
#define entryMode 0x06
#define displayOn 0x0F
#define displayOff 0x08
#define cursorBlinkOff 0x0E
#define cursorOff 0x0C
#define cursorShiftLeft 0x10
#define cursorShiftRight 0x14
#define functionSet8Bit 0x3C
#define functionSet4Bit 0x2C

void LCD_voidInit();

void LCD_voidSendCommand(u8 command);

void LCD_voidSendChar(u8 Char);

void LCD_voidSendNumber(u16 number);

void LCD_voidSendString(u8 *string);

void LCD_voidSetCursorPosition(u8 position);

#endif