#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "STD_TYPES.h"

void LCD_voidInit();

void LCD_voidSendCommand(u8 command);

void LCD_voidSendChar(u8 Char);

void LCD_voidSendNumber(s32 number);

void LCD_voidSendFloat(f32 number);

void LCD_voidSendString(u8 *string);

void LCD_voidSetCursorPosition(u8 row, u8 col);

#endif