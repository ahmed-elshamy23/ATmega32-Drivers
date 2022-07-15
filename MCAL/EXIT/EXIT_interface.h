#ifndef EXIT_INTERFACE_H
#define EXIT_INTERFACE_H

#include "STD_TYPES.h"

#define MCUCR *((volatile u8 *)(0x55))
#define MCUCSR *((volatile u8 *)(0x54))
#define GICR *((volatile u8 *)(0x5B))
#define SREG *((volatile u8 *)(0x5F))

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define ISC2 6

#define INT0 0
#define INT1 1
#define INT2 2

#define INT0_BIT 6
#define INT1_BIT 7
#define INT2_BIT 5

#define GLOBAL_INTERRUPT 7

#define RISING_EDGE 0
#define FALLING_EDGE 1
#define LOW_LEVEL 2
#define ANY_CHANGE 3

#define NULL 0

void EXIT_voidEnableGlobalInterrupt();

void EXIT_voidInit(u8 peripheral, u8 mode);

void EXIT_voidSetCallbackINT0(void (*ptr)());

void EXIT_voidSetCallbackINT1(void (*ptr)());

void EXIT_voidSetCallbackINT2(void (*ptr)());

void __vector_1(void) __attribute__((signal));

void __vector_2(void) __attribute__((signal));

void __vector_3(void) __attribute__((signal));

#endif