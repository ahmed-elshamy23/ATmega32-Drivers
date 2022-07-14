#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KPD_interface.h"
#include <util/delay.h>

u8 KPD_BUTTONS[4][4] = {{7, 8, 9, '/'}, {4, 5, 6, '*'}, {1, 2, 3, '-'}, {'c', 0, '=', '+'}};

void KPD_voidInit(u8 portNumber)
{
    DIO_voidSetPinDirection(portNumber, R0, OUTPUT);
    DIO_voidSetPinDirection(portNumber, R1, OUTPUT);
    DIO_voidSetPinDirection(portNumber, R2, OUTPUT);
    DIO_voidSetPinDirection(portNumber, R3, OUTPUT);

    DIO_voidSetPinDirection(portNumber, C0, INPUT);
    DIO_voidSetPinDirection(portNumber, C1, INPUT);
    DIO_voidSetPinDirection(portNumber, C2, INPUT);
    DIO_voidSetPinDirection(portNumber, C3, INPUT);

    DIO_voidSetPortValue(portNumber, ALL_OUTPUT);
}

u8 KPD_u8GetPresseddKey(u8 portNumber)
{
    u8 row, col, pressed = NOT_PRESSED;
    for (row = ROW_START; row <= ROW_END; row++)
    {
        DIO_voidSetPinValue(portNumber, row, LOW);
        for (col = COL_START; col <= COL_END; col++)
        {
            if (DIO_u8GetPinValue(portNumber, col) == LOW)
            {
                pressed = KPD_BUTTONS[row - ROW_START][col - COL_START];
                _delay_ms(10);
            }
            DIO_voidSetPinValue(portNumber, row, HIGH);
        }
    }
    return pressed;
}