#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "STD_TYPES.h"

#define LEFT_ADJUST 0
#define RIGHT_ADJUST 1

#define SFIOR *((volatile u8 *)(0x50))
#define ADMUX *((volatile u8 *)(0x27))
#define ADCSRA *((volatile u8 *)(0x26))
#define ADCH *((volatile u8 *)(0x25))
#define ADCL *((volatile u8 *)(0x24))
#define ADCLH *((volatile u16 *)(0x24))

#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3 3
#define MUX4 4
#define ADLAR 5
#define REFS0 6
#define REFS1 7

#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#define ADIF 4
#define ADATE 5
#define ADSC 6
#define ADEN 7

#define ADTS0 5
#define ADTS1 6
#define ADTS2 7

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

#define AVCC 0
#define AREF 1
#define INTERNAL_VREF 2

#define SINGLE_CONVERSION 0
#define AUTO_TRIGGER 1

#define FREE_RUNNING 0
#define ANALOG_COMPARATOR 1
#define EXIT0 2
#define TIMER0_MATCH 3
#define TIMER0_OVERFLOW 4
#define TIMER1_MATCH 5
#define TIMER1_OVERFLOW 6
#define TIMER1_CAPTURE 7

#define NULL 0

void ADC_voidInit(u8 channel);

void ADC_voidStartConversion();

void ADC_voidInterruptEnable();

u16 ADC_u16GetResult();

void __vector_16(void) __attribute__((signal));

void ADC_voidSetCallback(void (*ptr)());

#endif