#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

#define LCD_8BIT 0
#define LCD_4BIT 1

#define ASCII_NUMBERS_START 48

#define clearDisplay 0x01
#define returnHome 0x02
#define entryMode 0x06
#define displayOn 0x0F
#define displayOff 0x08
#define displayShiftLeft 0x1C
#define displayShiftRight 0x18
#define cursorBlinkOff 0x0E
#define cursorOff 0x0C
#define cursorShiftLeft 0x10
#define cursorShiftRight 0x14
#define functionSet8Bit 0x3C
#define functionSet4Bit 0x2C

#endif