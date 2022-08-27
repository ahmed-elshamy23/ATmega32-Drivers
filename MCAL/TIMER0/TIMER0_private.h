#ifndef TIMER0_PRIVATE_H
#define TIMER0_PRIVATE_H

#define TCCR0 *((volatile u8 *)(0x53))
#define TCNT0 *((volatile u8 *)(0x52))
#define OCR0 *((volatile u8 *)(0x5C))
#define TIMSK *((volatile u8 *)(0x59))
#define TIFR *((volatile u8 *)(0x58))

#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7

#define TOIE 0
#define OCIE 1

#define TOV0 0
#define OCF0 1

#define NORMAL_MODE 0
#define CTC_MODE 1
#define PWM_MODE 2
#define FAST_PWM_MODE 3
#define COUNTER_MODE 4
#define EXT_RISING_EDGE 5
#define EXT_FALLING_EDGE 6

#define OVERFLOW 0
#define COMPARE_MATCH 1

#define OC0_PIN 3

#define OC0_SET 0
#define OC0_CLEAR 1
#define OC0_TOGGLE 2
#define OC0_INVERTING 3
#define OC0_NONINVERTING 4

#define TIMER0_COMP_ISR __vector_10
#define TIMER0_OVERFLOW_ISR __vector_11

#define NULL 0

#define CLOCK 8000000UL

#endif