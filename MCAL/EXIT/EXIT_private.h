#ifndef EXIT_PRIVATE_H
#define EXIT_PRIVATE_H

#define MCUCR *((volatile u8 *)(0x55))
#define MCUCSR *((volatile u8 *)(0x54))
#define GICR *((volatile u8 *)(0x5B))

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

#define RISING_EDGE 0
#define FALLING_EDGE 1
#define LOW_LEVEL 2
#define ANY_CHANGE 3

#define INT0_VECT __vector_1
#define INT1_VECT __vector_2
#define INT2_VECT __vector_3

#define NULL 0

#endif