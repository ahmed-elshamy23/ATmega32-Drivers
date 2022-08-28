#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

#define TCCR1A (*(volatile u8 *)(0x4F))
#define TCCR1B (*(volatile u8 *)(0x4E))
#define TCNT1 (*(volatile u16 *)(0x4C))
#define OCR1A (*(volatile u16 *)(0x4A))
#define OCR1B (*(volatile u16 *)(0x48))
#define ICR1 (*(volatile u16 *)(0x46))
#define TIMSK (*(volatile u8 *)(0x59))
#define TIFR (*(volatile u8 *)(0x58))

#define WGM10 0
#define WGM11 1
#define FOC1B 2
#define FOC1A 3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

#define TOIE1 2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5

#define TOV1 2
#define OCF1B 3
#define OCF1A 4
#define ICF1 5

#define COMP_A 0
#define COMP_B 1

#define TIMER1_NORMAL_MODE 0
#define TIMER1_CTC_MODE 1
#define TIMER1_PWM_MODE 2
#define TIMER1_FAST_PWM_MODE 3
#define TIMER1_FREQUENCY_PHASE_CORRECT 4

#define TOP_8BIT 0
#define TOP_9BIT 1
#define TOP_10BIT 2
#define TOP_ICR 3
#define TOP_OCR 4

#define TIMER1_PRESCALER_1 1
#define TIMER1_PRESCALER_8 8
#define TIMER1_PRESCALER_64 64
#define TIMER1_PRESCALER_256 256
#define TIMER1_PRESCALER_1024 1024
#define TIMER1_PRESCALER_EXT_FALLING_EDGE 11
#define TIMER1_PRESCALER_EXT_RISING_EDGE 12

#define OC1A_PIN 5
#define OC1B_PIN 4

#define OC1A_SET 0
#define OC1A_CLEAR 1
#define OC1A_TOGGLE 2
#define OC1A_INVERTING 3
#define OC1A_NONINVERTING 4

#define OC1B_SET 5
#define OC1B_CLEAR 6
#define OC1B_TOGGLE 7
#define OC1B_INVERTING 8
#define OC1B_NONINVERTING 9

#define ICU_INTERRUPT 0
#define COMP_A_INTERRUPT 1
#define COMP_B_INTERRUPT 2
#define OVF_INTERRUPT 3

#define RISING_EDGE 0
#define FALLING_EDGE 1

#define TIMER1_CAPTURE_ISR __vector_6
#define TIMER1_COMP_A_ISR __vector_7
#define TIMER1_COMP_B_ISR __vector_8
#define TIMER1_OVERFLOW_ISR __vector_9

#define NULL 0

#define CLOCK 8000000UL

#endif