#ifndef TIMER2_PRIVATE_H
#define TIMER2_PRIVATE_H

#include "STD_TYPES.h"

#define TIMSK *((volatile u8 *)(0x59))
#define TIFR *((volatile u8 *)(0x58))
#define SFIOR *((volatile u8 *)(0x50))
#define TCCR2 *((volatile u8 *)(0x45))
#define TCNT2 *((volatile u8 *)(0x44))
#define OCR2 *((volatile u8 *)(0x43))
#define ASSR *((volatile u8 *)(0x42))
#define DDRD *((volatile u8 *)(0x31))

#define OC2_PIN 7

#define CS20 0
#define CS21 1
#define CS22 2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2 7

#define TCR2UB 0
#define OCR2UB 1
#define TCN2UB 2
#define AS2 3

#define TOIE2 6
#define OCIE2 7

#define TOV2 6
#define OCF2 7

#define PSR2 1

#define TIMER2_PRESCALER_1 1
#define TIMER2_PRESCALER_8 8
#define TIMER2_PRESCALER_32 32
#define TIMER2_PRESCALER_64 64
#define TIMER2_PRESCALER_128 128
#define TIMER2_PRESCALER_256 256
#define TIMER2_PRESCALER_1024 1024

#define TIMER2_NORMAL_MODE 0
#define TIMER2_CTC_MODE 1
#define TIMER2_FAST_PWM_MODE 2
#define TIMER2_PHASE_CORRECT_PWM_MODE 3
#define TIMER2_ASYNCHRONOUS_MODE 4

#define TIMER2_OVERFLOW 0
#define TIMER2_COMPARE_MATCH 1

#define OC2_NON_INVERTING 0
#define OC2_INVERTING 1
#define OC2_DISCONNECTED 2
#define OC2_TOGGLE 3

#define TIMER2_OVERFLOW_ISR __vector_5
#define TIMER2_COMPARE_MATCH_ISR __vector_4

#define NULL 0

#define CLOCK 800000000UL

#endif