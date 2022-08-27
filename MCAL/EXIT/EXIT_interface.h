#ifndef EXIT_INTERFACE_H
#define EXIT_INTERFACE_H

#include "STD_TYPES.h"

void EXIT_voidInit(u8 peripheral, u8 mode);

void EXIT_voidSetCallbackINT0(void (*ptr)());

void EXIT_voidSetCallbackINT1(void (*ptr)());

void EXIT_voidSetCallbackINT2(void (*ptr)());

void INT0_VECT(void) __attribute__((signal));

void INT1_VECT(void) __attribute__((signal));

void INT2_VECT(void) __attribute__((signal));

#endif